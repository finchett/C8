#pragma once
#include <stdint.h>

extern uint8_t memory[];
extern uint8_t stack[];
extern uint16_t pc;
extern uint16_t ir;

void push(uint8_t n);
uint8_t pop();
