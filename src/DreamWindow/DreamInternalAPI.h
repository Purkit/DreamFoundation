#ifndef DREAM_INTERNAL_API
#define DREAM_INTERNAL_API

#include "DreamWindow.h"
#include <Dream/KeyCodes.h>
#include <stdint.h>

// Platform layer facing API:

void _dream_set_window_title(_DreamWindow *window, const char *title);
void _dream_set_window_size(_DreamWindow *window, uint32_t w, uint32_t h);
void _dream_get_window_size(_DreamWindow *window, uint32_t *w, uint32_t *h);
void _dream_set_window_shouldClose(_DreamWindow *window, bool v);
void _dream_set_window_isFullscreen(_DreamWindow *window, bool v);
bool _dream_is_window_fullscreen(_DreamWindow *window);
void _dream_set_window_isBorderless(_DreamWindow *window, bool v);
bool _dream_is_window_borderless(_DreamWindow *window);
void _dream_set_window_isResizable(_DreamWindow *window, bool v);
bool _dream_is_window_resizable(_DreamWindow *window);
void _dream_update_next_window(
    _DreamWindow *current_window, _DreamWindow *next_window
);

void _dream_register_keypress(_DreamWindow *w, KeyCode kc);
void _dream_register_keyrelease(_DreamWindow *w, KeyCode kc);

void _dream_register_mousebtn_press(_DreamWindow *w, MouseButtonCode mbc);
void _dream_register_mousebtn_release(_DreamWindow *w, MouseButtonCode mbc);

void _dream_update_mouse_pos(_DreamWindow *w, uint16_t x, uint16_t y);
void _dream_update_mouse_delta(_DreamWindow *w, int16_t dx, int16_t dy);

void _dream_update_lastbtnpress_pos(_DreamWindow *w, uint16_t x, uint16_t y);

void _dream_update_mouse_motion_timestamp(_DreamWindow *w, uint32_t t);

void _dream_update_lastbtnpress_timestamp(_DreamWindow *w, uint32_t t);

#endif // DREAM_INTERNAL_API
