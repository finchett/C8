#pragma once
#include <stdint.h>

extern int16_t memory[];
extern int16_t stack[];
extern int16_t pc;
extern int16_t ir;

void push(int16_t n);
int16_t pop();
