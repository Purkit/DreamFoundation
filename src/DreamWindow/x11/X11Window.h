#ifndef X11_WINDOW
#define X11_WINDOW

// X11 platform specific window data

#include <xcb/xproto.h>

typedef struct X11Window {
    xcb_window_t handle;
    bool pending_pointer_grab;
} X11Window;

#endif // X11_WINDOW
