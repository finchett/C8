#include <stdint.h>
#include "memory.h"

int16_t memory[4096];
int16_t stack[32];

static int stack_index = 0;

void push(int16_t n) {
    stack[stack_index++] = n;
};

int16_t pop() {
    return stack[stack_index--];
};