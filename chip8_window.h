#pragma once
#include <gtk/gtk.h>
#include "chip8_application.h"

#define CHIP8_TYPE_WINDOW (chip8_window_get_type())
G_DECLARE_FINAL_TYPE(Chip8Window, chip8_window, CHIP8, Window, GtkApplicationWindow)

Chip8Window * chip8_window_new (Chip8Application *app);
