#include "chip8_application.h"
#include "chip8_window.h"
#include "chip8_display.h"

struct _Chip8Application {
  GObject parent;
  GtkWindow window;
  GtkWidget *gl_area;
};

G_DEFINE_TYPE(Chip8Application, chip8_application, G_TYPE_OBJECT)

static void chip8_application_class_init(Chip8ApplicationClass *class) {
  return;
};

static void chip8_application_init(Chip8Application *instance) {
  return;
};

Chip8Application *chip8_application_new(GtkWindow *window) {
  Chip8Application *instance;

  instance = g_object_new(CHIP8_TYPE_APPLICATION, NULL);
  instance->gl_area = (chip8_add_display(window));

  return instance;
};