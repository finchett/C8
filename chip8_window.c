#include <gtk/gtk.h>
#include "chip8_window.h"
#include "chip8_application.h"
#include "chip8_display.h"
#include "chip8_input.h"
#include "chip8_memory.h"
#include <stdio.h>
#include "debug.h"

struct _Chip8Window {
  GtkApplicationWindow parent;
  GtkWidget *gl_area;
};


G_DEFINE_TYPE(Chip8Window, chip8_window, GTK_TYPE_APPLICATION_WINDOW)

static void chip8_window_class_init() { return; };

static void chip8_window_init(Chip8Window *self) {

  GtkWindow *cast_window_self = GTK_WINDOW(self);

  // window
  gtk_window_set_title(cast_window_self, "Window");
  gtk_window_set_default_size(cast_window_self, 400, 300);
  gtk_window_present(cast_window_self);

  // gl_area (display)
  self->gl_area = (chip8_add_display(cast_window_self));
  



  //input
  chip8_add_keyboard_input(cast_window_self);

  return;
};

Chip8Window *chip8_window_new(Chip8Application *app) {
  Chip8Window *instance;

  return g_object_new(CHIP8_TYPE_WINDOW, "application", app, NULL);
}
