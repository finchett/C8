#include "chip8_application.h"
#include "chip8_window.h"
#include "chip8_display.h"
#include "chip8_timer.h"
#include "chip8_memory.h"
#include "chip8_input.h"
#include "chip8_font.h"
#include <stdint.h>
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

  uint8_t *memory;
  uint8_t *stack;

  uint16_t *pc;
  uint16_t *ir;
};

G_DEFINE_TYPE(Chip8Application, chip8_application, G_TYPE_OBJECT)

static void chip8_application_class_init(Chip8ApplicationClass *class) {
  return;
};

static void chip8_application_init(Chip8Application *instance) {
  return;
};

static uint16_t fetch();
static void decode();
static void execute();

static void on_tick(Chip8Timer *timer) {

  // todo: multithread rather than using gtk timeouts which are not precise enough.

  uint16_t ins = fetch();
  decode();
  execute();

}

static void read_rom() {
    FILE *file;

    // Open the file for reading
    file = fopen("ibm.ch8", "rb");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return 1;
    }

    // Read the file into the buffer
    size_t bytesRead = fread(memory, sizeof(uint8_t), 4096, file);

    // Close the file
    fclose(file);

    printf("Read %zu bytes from the file.\n", bytesRead);
};

Chip8Application *chip8_application_new(GtkWindow *window) {
  Chip8Application *self = g_object_new(CHIP8_TYPE_APPLICATION, NULL);

  // load rom
  read_rom();



  //timer
  self->timer = chip8_timer_new(255, 1);
  g_signal_connect(self->timer, "on_tick", (GCallback) on_tick, NULL);


  // display
  self->gl_area = (chip8_add_display(window));

  // input
  self->input = chip8_add_keyboard_input(window);

  //memory
  self->memory = memory;
  self->stack = stack;
  self->pc = &pc;
  self->ir = &ir;



  return self;
};


static uint16_t fetch() {
  char byte1 = memory[pc];
  char byte2 = memory[pc + 1];

  pc += 2;
  
  //returns joined bytes
  return (uint16_t) ((byte1 << 8) | byte2);
};

static void decode() {

};

static void execute() {

};