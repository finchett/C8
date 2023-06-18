#pragma once
#include <gtk/gtk.h>

#define CHIP8_TYPE_APPLICATION (chip8_application_get_type())

G_DECLARE_FINAL_TYPE(Chip8Application, chip8_application, CHIP8, APPLICATION, GtkApplication)

Chip8Application *chip8_application_new();