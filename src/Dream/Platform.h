#ifndef DREAM_PLATFORM_H
#define DREAM_PLATFORM_H

#if defined(_WIN32)
#define DREAM_PLATFORM_WIN32
#elif defined(__linux__)
#define DREAM_PLATFORM_LINUX
#elif defined(__APPLE__)
#define DREAM_PLATFORM_MACOS
#else
#error "No supported platform (OS) detected."
#endif

#if defined(__EMSCRIPTEN__)
#define DREAM_PLATFORM_WEB
#endif

#endif // !DREAM_PLATFORM_H
