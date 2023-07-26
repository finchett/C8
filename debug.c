#include <stdio.h>
#include <epoxy/gl.h>
#include "debug.h"
#include "chip8_input.h"


// Gl context must be available.
void print_opengl_info() {
  const GLubyte *renderer = glGetString(GL_RENDERER); // get renderer string
  const GLubyte *version = glGetString(GL_VERSION);   // version as a string
  printf("Renderer: %s\n", renderer);
  printf("OpenGL version supported %s\n", version);
};

void say_hello() {
  printf("hello\n");
}

void print_input_state() {

  for (int i = 1; i < 17; i++) {
    printf("%x\n", chip8_input[(i-1)]);
    if (i%4 == 0) {
      printf("\n");
    }
  }

  printf("\n");
};