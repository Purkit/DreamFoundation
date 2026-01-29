#include "DreamInternalAPI.h"

void _dream_set_window_title(_DreamWindow *window, const char *title) {
    window->title = title;
}

void _dream_set_window_size(_DreamWindow *window, uint32_t w, uint32_t h) {
    window->width  = w;
    window->height = h;
}

void _dream_get_window_size(_DreamWindow *window, uint32_t *w, uint32_t *h) {
    *w = window->width;
    *h = window->height;
}

void _dream_set_window_shouldClose(_DreamWindow *window, bool v) {
    window->shouldClose = v;
}

void _dream_set_window_isFullscreen(_DreamWindow *window, bool v) {
    window->isFullscreen = v;
}
bool _dream_is_window_fullscreen(_DreamWindow *window) {
    return window->isFullscreen;
}

void _dream_set_window_isBorderless(_DreamWindow *window, bool v) {
    window->isBorderless = v;
}
bool _dream_is_window_borderless(_DreamWindow *window) {
    return window->isBorderless;
}

void _dream_set_window_isResizable(_DreamWindow *window, bool v) {
    window->isResizable = v;
}
bool _dream_is_window_resizable(_DreamWindow *window) {
    return window->isResizable;
}

void _dream_update_next_window(
    _DreamWindow *current_window, _DreamWindow *next_window
) {
    current_window->next = next_window;
}

void _dream_register_keypress(_DreamWindow *w, KeyCode kc) {
    w->inputState.ks.keyState_bits[kc / 64] |= (1ULL << (kc % 64));
}

void _dream_register_keyrelease(_DreamWindow *w, KeyCode kc) {
    w->inputState.ks.keyState_bits[kc / 64] &= ~(1ULL << (kc % 64));
}

void _dream_register_mousebtn_press(_DreamWindow *w, MouseButtonCode mbc) {
    w->inputState.ps.mouseBtnState_bits |= (1 << mbc);
    w->inputState.ps.last_pressed_btn = (MouseButtonCode)mbc;
}

void _dream_register_mousebtn_release(_DreamWindow *w, MouseButtonCode mbc) {
    w->inputState.ps.mouseBtnState_bits &= ~(1 << mbc);
}

void _dream_update_mouse_pos(_DreamWindow *w, uint16_t x, uint16_t y) {
    w->inputState.ps.position.x = x;
    w->inputState.ps.position.y = y;
}

void _dream_update_mouse_delta(_DreamWindow *w, int16_t dx, int16_t dy) {}

void _dream_update_lastbtnpress_pos(_DreamWindow *w, uint16_t x, uint16_t y) {
    w->inputState.ps.last_btn_press_position.x = x;
    w->inputState.ps.last_btn_press_position.y = y;
}

void _dream_update_mouse_motion_timestamp(_DreamWindow *w, uint32_t t) {
    w->inputState.ps.motion_timestamp = t;
}

void _dream_update_lastbtnpress_timestamp(_DreamWindow *w, uint32_t t) {
    w->inputState.ps.last_btn_press_timestamp = t;
}
