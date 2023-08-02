#include <stdint.h>
#include <gtk/gtk.h>
#include "chip8_memory.h"

uint16_t pc = 0;
uint16_t ir = 0;
uint8_t memory[4096];
uint16_t stack[32];
uint16_t vr[16];

static int stack_index = 0;


void push(uint16_t n) {
    stack[stack_index++] = n;
};


uint16_t pop() {
    return stack[--stack_index];
};

void read_rom(char *rom)
{
  FILE *file;

  // Open the file for reading
  file = fopen(rom, "rb");
  if (file == NULL)
  {
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
