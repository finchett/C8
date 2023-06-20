#include "chip8_window.h"
#include "chip8_application.h"
#include <epoxy/gl.h>
#include <gtk/gtk.h>

struct _Chip8Window {
  GtkApplicationWindow parent;
  GtkWidget *gl_area;
};

G_DEFINE_TYPE(Chip8Window, chip8_window, GTK_TYPE_APPLICATION_WINDOW)

static void init_buffer_objects(){};

static bool on_render(GtkGLArea *area, GdkGLContext *context) {
  glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  return false;
}

static void on_realize(GtkGLArea *area, GdkGLContext *context) {
  gtk_gl_area_make_current(area);
  init_buffer_objects();
};

static void chip8_window_class_init() { return; };

static void chip8_window_init(Chip8Window *self) {

  GtkWindow *cast_window_self = GTK_WINDOW(self);
  GtkWidget *gl_area = gtk_gl_area_new();

  // gl_area
  g_signal_connect(gl_area, "render", G_CALLBACK(on_render), NULL);
  g_signal_connect(gl_area, "realize", G_CALLBACK(on_realize), NULL);
  self->gl_area = gl_area;
  gtk_window_set_child(cast_window_self, gl_area);

  // window
  gtk_window_set_title(cast_window_self, "Window");
  gtk_window_set_default_size(cast_window_self, 400, 300);
  gtk_window_present(cast_window_self);

  return;
};

Chip8Window *chip8_window_new(Chip8Application *app) {
  Chip8Window *instance;

  return g_object_new(CHIP8_TYPE_WINDOW, "application", app, NULL);
}
