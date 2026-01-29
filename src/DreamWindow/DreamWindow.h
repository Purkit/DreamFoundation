#ifndef DREAM_WINDOW_H
#define DREAM_WINDOW_H

#include <Dream/KeyCodes.h>
#include <stdint.h>

#include "Dream/_callbackSig.h"
#include "wayland/WaylandWindow.h"
#include "win32/Win32Window.h"
#include "x11/X11Window.h"

typedef struct PointerState {
    struct Vector2i {
        float x, y;
    } position, relative_motion, last_btn_press_position;
    uint32_t motion_timestamp;
    uint32_t relative_motion_timestamp;
    uint32_t last_btn_press_timestamp;
    uint8_t mouseBtnState_bits;
    MouseButtonCode last_pressed_btn;
} PointerState;

typedef struct KeyboardState {
    uint32_t last_keyPress_time;
    uint64_t keyState_bits[2];
} KeyboardState;

typedef struct InputState {
    PointerState ps;
    KeyboardState ks;
} InputState;

typedef struct DreamWindow {
    struct DreamWindow *next;

    // Platform Independent Window State:
    const char *title;
    uint32_t width;
    uint32_t height;
    // bool resized;
    bool shouldClose;
    bool isFullscreen;
    bool isBorderless;
    bool isResizable;

    InputState inputState;

    struct {
        DWindowResizeFn onResize;
        DWindowFrameDoneFn onFrameDone;
        DWindowKeyEventFn onKeyEvent;
        DWindowMouseBtnEventFn onMouseBtnEvent;
        DWindowMouseMoveEventFn onMouseMove;
        DWindowMouseScrollEventFn onScroll;
        DWindowFocusLossFn onFocusLoss;
        DWindowFocusGainFn onFocusGain;
        DWindowMouseEnterFn onMouseEnter;
        DWindowMouseLeaveFn onMouseLeave;
        DWindowCloseBtnPressFn onCloseBtnPress;
        DWindowMaximizeFn onWindowMaximize;
        DWindowMinimizeFn onWindowMinimize;
        void *user_data;
    } callbacks;

    void *user_data;

    // Platform Specific Window State:

#ifdef DREAM_WINDOWING_PLATFORM_X11
    X11Window x11Window;
#endif
#ifdef DREAM_WINDOWING_PLATFORM_WAYLAND
    WayWaylandWindow waylandWindow;
#endif
#ifdef DREAM_WINDOWING_PLATFORM_WIN32
    Win32Window win32Window;
#endif
} _DreamWindow;

#endif // DREAM_WINDOW_H
