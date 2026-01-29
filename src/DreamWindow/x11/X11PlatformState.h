#ifndef X11_PLATFORM_STATE_H
#define X11_PLATFORM_STATE_H

#include <stdint.h>
#include <xcb/xcb.h>
#include <xcb/xcb_keysyms.h>
#include <xcb/xproto.h>

#include <EGL/egl.h>

struct X11Window;

typedef struct X11PlatformState {
    xcb_connection_t *connection;
    xcb_screen_t *screen;

    xcb_atom_t wm_protocols;
    xcb_atom_t wm_delete_window;

    xcb_atom_t wm_name;
    xcb_atom_t net_wm_name;
    xcb_atom_t utf8_string;

    xcb_atom_t net_wm_state;
    xcb_atom_t net_wm_state_fullscreen;

    // xcb_atom_t net_wm_window_type;
    // xcb_atom_t net_wm_window_type_normal;
    // xcb_atom_t net_wm_window_type_splash;
    xcb_atom_t motif_wm_hints;

    xcb_key_symbols_t *xcb_keysym;

    EGLDisplay egl_display;
    bool egl_initialized;

    bool xi_available;
    int xi_primary_pointer_dev_id;

    xcb_cursor_t invisible_cursor;
    bool pointer_locked;

    struct X11Window *window_list_head;
    uint32_t window_count;
} X11PlatformState;

#endif // X11_PLATFORM_STATE_H
