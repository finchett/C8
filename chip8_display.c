#include <epoxy/gl.h>
#include "gtk/gtk.h"

/* TODO: clean up. */

GLuint vbo = 0;
GLuint vao = 0;
GLuint shader_programme;
GLuint texture;
int a;

float texture_data[64 * 32 * 3];

float points[] = {
  /* TODO: remove z coords, fix in vertex shader. */
    -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
    -1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
    1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
    1.0f, 1.0f, 0.0f, 1.0f, 1.0f};

static bool on_render(GtkGLArea *area, GdkGLContext *context)
{
  glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  glUseProgram(shader_programme);

  /* Texture */
  glBindTexture(GL_TEXTURE_2D, texture);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 64, 32, 0, GL_RGB, GL_FLOAT, texture_data);

  glBindVertexArray(vao);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
  glBindVertexArray(0);

  glFlush();

  return false;
}

int one_d_index(uint16_t x, uint16_t y) {
  x = x % 64;
  y = y % 32;
  return (((((32-y) * 64) + x)) * 3);
}


static void on_realize(GtkGLArea *area, GdkGLContext *context)
{
  print_opengl_info();
  gtk_gl_area_make_current(area);

  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(points) * sizeof(float), points, GL_STATIC_DRAW);

  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, NULL);

  const char *vertex_shader =
      "#version 400\n"
      "layout (location = 0) in vec3 vp;"
      "layout (location = 1) in vec2 tex;"
      "out vec2 Texcoord;"
      "void main() {"
      "  gl_Position = vec4(vp, 1.0);"
      "  Texcoord = tex;"
      "}";

  const char *fragment_shader =
      "#version 400\n"
      "out vec4 frag_colour;"
      "in vec2 Texcoord;"
      "uniform sampler2D tex;"
      "void main() {"
      "  frag_colour = texture(tex, Texcoord);"
      "}";

  GLuint vs = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vs, 1, &vertex_shader, NULL);
  glCompileShader(vs);
  GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fs, 1, &fragment_shader, NULL);
  glCompileShader(fs);

  shader_programme = glCreateProgram();

  glAttachShader(shader_programme, vs);
  glAttachShader(shader_programme, fs);
  glLinkProgram(shader_programme);

  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  /* Texture attribute */
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, sizeof(float) * 3);
};

GtkWidget *chip8_add_display(GtkWindow *window)
{
  GtkWidget *gl_area = gtk_gl_area_new();
  g_signal_connect(gl_area, "render", G_CALLBACK(on_render), NULL);
  g_signal_connect(gl_area, "realize", G_CALLBACK(on_realize), NULL);
  gtk_window_set_child(window, gl_area);
  return gl_area;
}