#ifndef DREAM_WINDOW_PUBLIC_API
#define DREAM_WINDOW_PUBLIC_API

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "KeyCodes.h"
#include "_callbackSig.h"

typedef struct DreamWindow DreamWindow;

typedef struct DreamWindowCallbacks {
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
} DreamWindowCallbacks;

typedef struct DreamWindowDesc {
    uint32_t width;
    uint32_t height;
    uint32_t min_width;
    uint32_t min_height;
    uint32_t max_width;
    uint32_t max_height;
    const char *title;
    bool fullscreen;
    bool borderless;
    bool resizable;
    const DreamWindowCallbacks *callbacks;
    void *user_data;
} DreamWindowDesc;

DreamWindowDesc DreamDefaultWindowDescriptor();

DreamWindow *DreamWindowCreate(const DreamWindowDesc *desc);
void DreamWindowDestroy(DreamWindow *window);

void DreamShowWindow(DreamWindow *window);
void DreamSetWindowTitle(DreamWindow *window, const char *title);
void DreamSetMaxWindowSize(DreamWindow *window, uint32_t w, uint32_t h);
void DreamSetMinWindowSize(DreamWindow *window, uint32_t w, uint32_t h);
void DreamMakeWindowFullscreen(DreamWindow *window, bool flag);
void DreamMakeWindowBorderless(DreamWindow *window, bool flag);
void DreamMakeWindowUnresizable(DreamWindow *window, bool flag);

void DreamSetPointerLock(DreamWindow *window, bool flag);
void DreamSetPointerVisibility(DreamWindow *window, bool flag);
void DreamEnableRawMouseMotion(bool flag);

void DreamPollEvents(DreamWindow *window);
void DreamWaitForEvent(DreamWindow *window);
void DreamWaitForEventTill(DreamWindow *window, double timeout);
void DreamWindowRegisterCallbacks(
    DreamWindow *window, const DreamWindowCallbacks *callbacks
);

bool DreamWindowShouldClose(DreamWindow *window);

KeyState DreamGetKeyState(DreamWindow *window, KeyCode key);
KeyState DreamGetMouseBtnState(DreamWindow *window, MouseButtonCode key);

bool DreamIsKeyPressed(DreamWindow *window, KeyCode key);
bool DreamIsKeyReleased(DreamWindow *window, KeyCode key);
bool DreamIsMouseBtnPressed(DreamWindow *window, MouseButtonCode key);
bool DreamIsMouseBtnReleased(DreamWindow *window, MouseButtonCode key);

void DreamGetMousePosition(DreamWindow *window, float *x, float *y);
float DreamGetMouseX(DreamWindow *window);
float DreamGetMouseY(DreamWindow *window);

#ifdef __cplusplus
}
#endif

#endif // !DREAM_WINDOW_PUBLIC_API
