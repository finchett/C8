#include "chip8_application.h"
#include "chip8_window.h"

struct _Chip8Application {
  GtkApplication parent;
};

G_DEFINE_TYPE(Chip8Application, chip8_application, GTK_TYPE_APPLICATION)

static void chip8_application_class_init(Chip8ApplicationClass *class) {
  return;
};

static void chip8_application_init(Chip8Application *instance) { return; };


static void activate (Chip8Application *app)
{
  Chip8Window *window;
  window = chip8_window_new(app);

};

Chip8Application *chip8_application_new() {
  Chip8Application *instance;

  instance = g_object_new(CHIP8_TYPE_APPLICATION, "application-id",
                          "com.github.sfinche.C8", "flags",
                          G_APPLICATION_HANDLES_OPEN, NULL);

  g_signal_connect(instance, "activate", G_CALLBACK (activate), NULL);

  return instance;
};
