#ifndef DREAM_PUBLIC_API
#define DREAM_PUBLIC_API

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum DreamLogLevel {
    DREAM_LOG_TRACE,
    DREAM_LOG_INFO,
    DREAM_LOG_DEBUG,
    DREAM_LOG_WARNING,
    DREAM_LOG_CRITICAL,
    DREAM_LOG_FATAL,
} DreamLogLevel;

typedef enum DreamLogSink {
    DREAM_LOG_SINK_STDOUT = 1 << 0,
    DREAM_LOG_SINK_STDERR = 1 << 1,
    DREAM_LOG_SINK_FILE   = 1 << 2,
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
} DreamLoggerConfig;

typedef void *(*DreamUserAllocFn)(
    size_t size, size_t alignment, void *user_data
);
typedef void (*DreamUserFreeFn)(void *ptr, void *user_data);

typedef struct DreamUserAllocator {
    DreamUserAllocFn alloc;
    DreamUserFreeFn free;
    void *user_data;
} DreamUserAllocator;

typedef struct DreamConfig {
    bool enable_logging;
    const DreamLoggerConfig *loggerConfig;
    bool enable_windowing_subsystem;
    bool enable_audio_subsystem;
    bool use_custom_allocator;
    const DreamUserAllocator *allocator;
    void *user_data;
} DreamConfig;

bool DreamInit(const DreamConfig *config);
void DreamShutdown();

#ifdef __cplusplus
}
#endif

#endif // !DREAM_PUBLIC_API
