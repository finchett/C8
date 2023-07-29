#pragma once
#include "gtk/gtk.h"

GtkWidget *chip8_add_display(GtkWindow *window);
int one_d_index(uint16_t x, uint16_t y);
extern float texture_data[64 * 32 * 3];
