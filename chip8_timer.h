#pragma once
#include <gtk/gtk.h>

#define CHIP8_TYPE_TIMER ( chip8_timer_get_type() )

G_DECLARE_FINAL_TYPE(Chip8Timer, chip8_timer, CHIP8, TIMER, GObject);

Chip8Timer *chip8_timer_new();