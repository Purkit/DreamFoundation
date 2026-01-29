#ifndef _CALLBACK_FUNCTION_SIGNATURES
#define _CALLBACK_FUNCTION_SIGNATURES

#include "KeyCodes.h"

typedef struct DreamWindow DreamWindow;

// Callback function signatures:
typedef void (*DWindowResizeFn)(DreamWindow *window, void *user_data);
typedef void (*DWindowFrameDoneFn)(
    DreamWindow *window, double time, void *user_data
);
typedef void (*DWindowKeyEventFn)(
    DreamWindow *window, KeyCode key, KeyAction action, void *user_data
);
typedef void (*DWindowMouseBtnEventFn)(
    DreamWindow *window, MouseButtonCode btn, KeyAction action, void *user_data
);
typedef void (*DWindowMouseMoveEventFn)(
    DreamWindow *window, float xpos, float ypos, void *user_data
);
typedef void (*DWindowMouseScrollEventFn)(
    DreamWindow *window, float amt, ScrollDir dir, void *user_data
);
typedef void (*DWindowFocusLossFn)(DreamWindow *window, void *user_data);
typedef void (*DWindowFocusGainFn)(DreamWindow *window, void *user_data);
typedef void (*DWindowMouseEnterFn)(DreamWindow *window, void *user_data);
typedef void (*DWindowMouseLeaveFn)(DreamWindow *window, void *user_data);
typedef void (*DWindowCloseBtnPressFn)(DreamWindow *window, void *user_data);
typedef void (*DWindowMaximizeFn)(DreamWindow *window, void *user_data);
typedef void (*DWindowMinimizeFn)(DreamWindow *window, void *user_data);

#endif // !_CALLBACK_FUNCTION_SIGNATURES
