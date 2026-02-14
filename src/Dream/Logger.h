#ifndef DREAM_INTERNAL_LOGGER
#define DREAM_INTERNAL_LOGGER

#include <stdint.h>
#include <stdio.h>
typedef enum DreamLogLevel {
    DREAM_LOG_TRACE,
    DREAM_LOG_INFO,
    DREAM_LOG_DEBUG,
    DREAM_LOG_WARNING,
    DREAM_LOG_CRITICAL,
    DREAM_LOG_FATAL,
} DreamLogLevel;

typedef enum DreamLogSink {
    DREAM_LOG_SINK_STDOUT      = 1 << 0,
    DREAM_LOG_SINK_STDERR      = 1 << 1,
    DREAM_LOG_SINK_FILE        = 1 << 2,
    DREAM_LOG_SINK_RING_BUFFER = 1 << 3,
} DreamLogSink;

typedef uint8_t DreamLogSinksBitmask;

typedef struct DreamLoggerConfig {
    bool enabled;
    bool use_color;
    bool use_emoji;
    bool show_time;
    bool show_thread;
    DreamLogLevel min_level;
    DreamLogSinksBitmask log_sinks;
    const char *logfile_path;

    uint32_t ring_buffer_lines;
    uint32_t ring_buffer_line_len;
} DreamLoggerConfig;

#if !defined(REMOVE_DREAM_LOGGER)

void DreamLoggerInit(const DreamLoggerConfig *config);
void DreamLoggerShutdown();

void DreamLog(DreamLogLevel level, const char *tags, const char *fmt, ...);

void DreamLoggerDumpRingBuffer(FILE *out);

#define dTrace(tag, ...)    DreamLog(DREAM_LOG_TRACE, tag, __VA_ARGS__)
#define dDebug(tag, ...)    DreamLog(DREAM_LOG_DEBUG, tag, __VA_ARGS__)
#define dInfo(tag, ...)     DreamLog(DREAM_LOG_INFO, tag, __VA_ARGS__)
#define dWarn(tag, ...)     DreamLog(DREAM_LOG_WARNING, tag, __VA_ARGS__)
#define dCritical(tag, ...) DreamLog(DREAM_LOG_CRITICAL, tag, __VA_ARGS__)
#define dFatal(tag, ...)    DreamLog(DREAM_LOG_FATAL, tag, __VA_ARGS__)

#else
#define dTrace(tag, ...)    ((void)0)
#define dDebug(tag, ...)    ((void)0)
#define dInfo(tag, ...)     ((void)0)
#define dWarn(tag, ...)     ((void)0)
#define dCritical(tag, ...) ((void)0)
#define dFatal(tag, ...)    ((void)0)
#endif // !REMOVE_DREAM_LOGGER

#endif // !DREAM_INTERNAL_LOGGER
