#pragma once
#include <stdint.h>

extern uint8_t memory[];
extern uint16_t stack[];
extern uint16_t pc;
extern uint16_t ir;
extern uint16_t vr[];

void read_rom(char *rom);

void push(uint16_t n);
uint16_t pop();
