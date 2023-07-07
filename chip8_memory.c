#include <stdint.h>
#include "chip8_memory.h"

uint16_t pc = 0;
uint16_t ir = 0;
uint8_t memory[4096];
uint8_t stack[32];

static int stack_index = 0;

void push(uint8_t n) {
    stack[stack_index++] = n;
};

uint8_t pop() {
    return stack[stack_index--];
};