#pragma once
#include "gtk/gtk.h"

GtkWidget *chip8_add_display(GtkWindow *window);
extern float texture_data[64 * 32 * 3];