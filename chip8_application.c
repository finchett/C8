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
  uint16_t *stack;
  uint16_t *pc;
  uint16_t *ir;
};

G_DEFINE_TYPE(Chip8Application, chip8_application, G_TYPE_OBJECT)

static void chip8_application_class_init(Chip8ApplicationClass *class) {};

static void chip8_application_init(Chip8Application *instance) {};

static uint16_t fetch();
static void decode(uint16_t ins);
static void execute();

static void on_tick(Chip8Timer *timer, gpointer data) {

  Chip8Application *self = data;

  // todo: multithread rather than using gtk timeouts which are not precise enough.

  uint16_t ins = fetch();
  decode(ins);
  // execute();


  //TODO: move out of main thread. 
  // only queue redraw when display is called. Use flag as instructions will be executed off the main thread.
  gtk_gl_area_queue_render(self->gl_area);

}

static void read_rom() {
    FILE *file;

    // Open the file for reading
    file = fopen("ibm.ch8", "rb");
    if (file == NULL) {
        printf("Failed to open the file.\n");
    }

    // Read the file into the buffer (program starts at 0x200)
    size_t bytesRead = fread(memory + 0x200, sizeof(uint8_t), (4096) - 0x200, file);

    // set pc to 0x200
    pc = 0x200;

    // Close the file
    fclose(file);

    printf("Read %zu bytes from the file.\n", bytesRead);
};


Chip8Application *chip8_application_new(GtkWindow *window) {
  Chip8Application *self = g_object_new(CHIP8_TYPE_APPLICATION, NULL);

  // load rom
  read_rom();

  self->timer = chip8_timer_new(255, 17);
  g_signal_connect(self->timer, "on_tick", (GCallback) on_tick, (gpointer) self);

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
  uint16_t byte1 = memory[pc];
  uint16_t byte2 = memory[pc + 1];
  uint16_t ret;
  pc += 2;
  
  //returns joined bytes
  ret = (uint16_t) ((byte1 << 8) | byte2);
  return ret;
};

// todo: move elsewhere

static bool arr_equal(char arr1[], char arr2[], unsigned int size) {
  return !memcmp(arr1, arr2, size);
}

static void _00E0();
static void _1NNN(uint16_t nnn);
static void _6XNN(uint16_t vx, uint16_t nn);
static void _7XNN(uint16_t vx, uint16_t nn);
static void _ANNN(uint16_t nnn);
static void _DXYN(uint16_t x, uint16_t y, uint16_t n);

static void decode(uint16_t ins) {
  uint16_t nibbles[4] = {0};

  uint16_t mask = 0b0000000000001111;

  // storing nibbles in reverse order 
  nibbles[3] = ins & mask;
  nibbles[2] = (ins >> 4) & mask;
  nibbles[1] = (ins >> 8) & mask;
  nibbles[0] = (ins >> 12) & mask;

  switch (nibbles[0]) {
    case 0x00:
      char clearscreen[4] = {0x00, 0x00, 0x0e, 0x00};
      if (arr_equal(nibbles, clearscreen, sizeof(nibbles))) {
        _00E0();
      }
      break;

    case 0x01:
      _1NNN(ins & 0xFFF);
      break;

    case 0x06:
      _6XNN(nibbles[1], ins & 0x0FF);
      break;

    case 0x07:
      _7XNN(nibbles[1], ins & 0x0FF);
      break;
    
    case 0x0a:
      _ANNN(ins & 0xFFF);
      break;

    case 0x0d:
      _DXYN(nibbles[1], nibbles[2], nibbles[3]);
      break;
  }
};

static void execute() {

}


static void _00E0() {
  printf("clearscreen!\n");
}

static void _1NNN(uint16_t nnn) {
  pc = nnn;
  printf("jump!\n");
}

static void _6XNN(uint16_t vx, uint16_t nn) {
  printf("set register vx = nn!\n");
  vr[vx] = nn;
}

static void _7XNN(uint16_t vx, uint16_t nn) {
  vr[vx] += nn;
  printf("add value nn to register vx!\n");
}

static void _ANNN(uint16_t nnn) {
  ir = nnn;
  printf("set index register ir to NNN\n");
}

// macro?
static int one_d_index(uint16_t x, uint16_t y) {
  return (((((32-y) * 64) + x)) * 3);
}

static void _DXYN(uint16_t vx, uint16_t vy, uint16_t n) {

  /* keep 2d array in memory. 
    set values as per instruction. mark redraw needed flag.*/

  uint16_t x = vr[vx] & 63;
  uint16_t y = vr[vy] & 31;

  vr[0xF] = 0;


  uint8_t sprite_row;
  uint8_t state;

  // for y height
  for (uint16_t i = 0; i < n; i++) {
    /* get byte */
    sprite_row = memory[ir + i];

    // for x row
    for (uint8_t bit = 0; bit < 8; bit++) {
      state = (sprite_row >> (7-bit)) & 1;

      if (state == 1 && texture_data[one_d_index(x + bit, y+i)] == 1) {
        vr[0xF] = 1;
        texture_data[one_d_index(x + bit, y+i)] = 0;
      }

      if (state == 1 && texture_data[one_d_index(x + bit, y+i)] == 0) {
        texture_data[one_d_index(x + bit, y+i)] = 1;
      }

      if (x + bit >= 64) {break;}
      // break if end of screen row
    }

  }

  printf("draw!!!\n");
}


