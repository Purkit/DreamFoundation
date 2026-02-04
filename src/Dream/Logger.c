#ifndef REMOVE_DREAM_LOGGER

#include "Logger.h"

#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "Platform.h"

#if defined(DREAM_PLATFORM_WIN32)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#else
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>
#endif

typedef struct DreamLoggerState {
    bool initialized;
    bool enabled;
    bool use_color;
    bool use_emoji;
    bool show_time;
    bool show_thread;
    DreamLogLevel min_level;
    DreamLogSinksBitmask log_sinks;
    FILE *logfile;
#ifdef DREAM_PLATFORM_WIN32
    HANDLE console;
    WORD default_attributes;
#endif
} DreamLoggerState;

static DreamLoggerState g_logger;

static const char *dream_log_level_string(DreamLogLevel level) {
    switch (level) {
        case DREAM_LOG_TRACE:    return "TRACE";
        case DREAM_LOG_DEBUG:    return "DEBUG";
        case DREAM_LOG_INFO:     return "INFO ";
        case DREAM_LOG_WARNING:  return "WARN ";
        case DREAM_LOG_CRITICAL: return "CRITICAL";
        case DREAM_LOG_FATAL:    return "FATAL";
        default:                 return "?????";
    }
}

#if defined(DREAM_PLATFORM_WIN32)

static WORD dream_log_level_color(DreamLogLevel level) {
    switch (level) {
        case DREAM_LOG_TRACE: return FOREGROUND_INTENSITY;
        case DREAM_LOG_DEBUG:
            return FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
        case DREAM_LOG_INFO: return FOREGROUND_GREEN | FOREGROUND_INTENSITY;
        case DREAM_LOG_WARN:
            return FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
        case DREAM_LOG_ERROR: return FOREGROUND_RED | FOREGROUND_INTENSITY;
        case DREAM_LOG_FATAL:
            return FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_RED;
        default: return g_logger.default_attributes;
    }
}

static void dream_set_color(DreamLogLevel level) {
    if (!g_logger.use_color) return;
    SetConsoleTextAttribute(g_logger.console, dream_log_level_color(level));
}

static void dream_reset_color(void) {
    if (!g_logger.use_color) return;
    SetConsoleTextAttribute(g_logger.console, g_logger.default_attributes);
}

static uint32_t dream_thread_id(void) { return (uint32_t)GetCurrentThreadId(); }

static void dream_time_string(char *out, size_t size) {
    SYSTEMTIME t;
    GetLocalTime(&t);
    snprintf(
        out,
        size,
        "%02d:%02d:%02d.%03d",
        t.wHour,
        t.wMinute,
        t.wSecond,
        t.wMilliseconds
    );
}

#else /* POSIX */

static const char *dream_log_level_color_ansi(DreamLogLevel level) {
    switch (level) {
        case DREAM_LOG_TRACE:    return "\033[90m";
        case DREAM_LOG_DEBUG:    return "\033[36m";
        case DREAM_LOG_INFO:     return "\033[32m";
        case DREAM_LOG_WARNING:  return "\033[33m";
        case DREAM_LOG_CRITICAL: return "\033[31m";
        case DREAM_LOG_FATAL:    return "\033[1;31m";
        default:                 return "";
    }
}

static void dream_set_color(DreamLogLevel level) {
    if (g_logger.use_color) fputs(dream_log_level_color_ansi(level), stdout);
}

static void dream_reset_color(void) {
    if (g_logger.use_color) fputs("\033[0m", stdout);
}

static uint32_t dream_thread_id(void) {
    return (uint32_t)(uintptr_t)pthread_self();
}

static void dream_time_string(char *out, size_t size) {
    struct timeval tv;
    gettimeofday(&tv, NULL);

    struct tm tm;
    localtime_r(&tv.tv_sec, &tm);

    snprintf(
        out,
        size,
        "%02d:%02d:%02d.%03ld",
        tm.tm_hour,
        tm.tm_min,
        tm.tm_sec,
        tv.tv_usec / 1000
    );
}

void DreamLoggerInit(const DreamLoggerConfig *config) {
    memset(&g_logger, 0, sizeof(g_logger));

    g_logger.enabled     = config->enabled;
    g_logger.use_color   = config->use_color;
    g_logger.use_emoji   = config->use_emoji;
    g_logger.show_time   = config->show_time;
    g_logger.show_thread = config->show_thread;
    g_logger.min_level   = config->min_level;
    g_logger.log_sinks   = config->log_sinks;
    g_logger.initialized = true;

#ifdef DREAM_PLATFORM_WIN32
    g_logger.console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(g_logger.console, &info);
    g_logger.default_attributes = info.wAttributes;
#endif

    if ((g_logger.log_sinks & DREAM_LOG_SINK_FILE) && config->logfile_path) {
        g_logger.logfile = fopen(config->logfile_path, "w");
        if (!g_logger.logfile) {
            g_logger.log_sinks &= ~DREAM_LOG_SINK_FILE;
        }
    }
}

void DreamLoggerShutdown(void) {
    if (g_logger.logfile) {
        fclose(g_logger.logfile);
        g_logger.logfile = nullptr;
    }
    g_logger.initialized = false;
}

static void dream_write_stdout(const char *text) {
    fputs(text, stdout);
    fflush(stdout);
}

static void dream_write_stderr(const char *text) {
    fputs(text, stderr);
    fflush(stderr);
}

static void dream_write_file(const char *text) {
    if (g_logger.logfile) {
        fputs(text, g_logger.logfile);
        fflush(g_logger.logfile);
    }
}

static void
dream_dispatch_log(DreamLogLevel level, const char *formatted_line) {
    if (g_logger.log_sinks & DREAM_LOG_SINK_STDOUT) {
        dream_set_color(level);
        dream_write_stdout(formatted_line);
        dream_reset_color();
    }

    if (g_logger.log_sinks & DREAM_LOG_SINK_STDERR) {
        dream_set_color(level);
        dream_write_stderr(formatted_line);
        dream_reset_color();
    }

    if (g_logger.log_sinks & DREAM_LOG_SINK_FILE) {
        dream_write_file(formatted_line);
    }
}

void DreamLog(DreamLogLevel level, const char *category, const char *fmt, ...) {
    if (!g_logger.initialized || !g_logger.enabled) return;

    if (level < g_logger.min_level) return;

    char msg[1024];
    char line[1400];
    char time_buf[32] = {0};

    va_list args;
    va_start(args, fmt);
    vsnprintf(msg, sizeof(msg), fmt, args);
    va_end(args);

    if (g_logger.show_time) {
        dream_time_string(time_buf, sizeof(time_buf));
    }

    int offset = 0;

    if (g_logger.show_time)
        offset +=
            snprintf(line + offset, sizeof(line) - offset, "[%s] ", time_buf);

    offset += snprintf(
        line + offset,
        sizeof(line) - offset,
        "[%s] ",
        dream_log_level_string(level)
    );

    if (category && category[0])
        offset +=
            snprintf(line + offset, sizeof(line) - offset, "[%s] ", category);

    if (g_logger.show_thread)
        offset += snprintf(
            line + offset, sizeof(line) - offset, "[T:%u] ", dream_thread_id()
        );

    snprintf(line + offset, sizeof(line) - offset, "%s\n", msg);

    dream_dispatch_log(level, line);

    if (level == DREAM_LOG_FATAL) {
#if defined(_WIN32)
        DebugBreak();
#else
        __builtin_trap();
#endif
    }
}

#endif

#endif // !REMOVE_DREAM_LOGGER
