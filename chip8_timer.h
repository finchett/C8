#pragma once
#include <gtk/gtk.h>

#define CHIP8_TYPE_TIMER ( chip8_timer_get_type() )

G_DECLARE_FINAL_TYPE(Chip8Timer, chip8_timer, CHIP8, TIMER, GObject);

struct _Chip8Timer {
    GObject parent;
    u_int8_t tick;
    gint rate;
    guint on_tick_signal_id;
};

Chip8Timer *chip8_timer_new(uint8_t tick, int rate);