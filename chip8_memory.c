#include <stdint.h>
#include <gtk/gtk.h>
#include "chip8_memory.h"

#define MEMORY_BYTES 4096
#define STACK_SIZE 32
#define N_VARIABLE_REGISTERS 16
#define PROGRAM_OFFSET 0x200

uint16_t pc = 0;
uint16_t ir = 0;
uint8_t memory[MEMORY_BYTES];
uint16_t stack[STACK_SIZE];
uint16_t vr[N_VARIABLE_REGISTERS];

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
  size_t bytesRead = fread(memory + PROGRAM_OFFSET, sizeof(uint8_t), (MEMORY_BYTES) - PROGRAM_OFFSET, file);

  // set pc to 0x200
  pc = PROGRAM_OFFSET;

  // Close the file
  fclose(file);

  printf("Read %zu bytes from the file.\n", bytesRead);
};
