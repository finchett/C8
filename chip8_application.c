#include "chip8_application.h"
#include "chip8_window.h"
#include "chip8_display.h"
#include "chip8_timer.h"
#include "chip8_input.h"
#include "debug.h"

/*
  TODO: make child of GtkWidget https://docs.gtk.org/gtk4/class.Widget.html
*/ 

struct _Chip8Application {
  GObject parent;
  GtkWindow window;
  GtkWidget *gl_area;
  Chip8Timer *timer;
  int16_t *input;
};

G_DEFINE_TYPE(Chip8Application, chip8_application, G_TYPE_OBJECT)

static void chip8_application_class_init(Chip8ApplicationClass *class) {
  return;
};

static void chip8_application_init(Chip8Application *instance) {
  return;
};

static void on_tick(Chip8Timer *timer) {
  // printf("tick is: %d\n", timer->tick);
}

Chip8Application *chip8_application_new(GtkWindow *window) {
  Chip8Application *self = g_object_new(CHIP8_TYPE_APPLICATION, NULL);

  //timer
  self->timer = chip8_timer_new(255, 17);
  g_signal_connect(self->timer, "on_tick", (GCallback) on_tick, NULL);


  // display
  self->gl_area = (chip8_add_display(window));

  // input
  self->input = chip8_add_keyboard_input(window);



  return self;
};