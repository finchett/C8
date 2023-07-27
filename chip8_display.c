#include <epoxy/gl.h>
#include "gtk/gtk.h"
// globals for now...
GLuint vbo = 0;
GLuint vao = 0;
GLuint shader_programme;
GLuint texture;

float texture_data[2048];

// triangle for testing drawing
float points[] = {
    -1.0f, -1.0f, 0.0f,
    -1.0f, 1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,
    1.0f, 1.0f, 0.0f};

static bool on_render(GtkGLArea *area, GdkGLContext *context)
{
  glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  glUseProgram(shader_programme);

  // update texture
  glBindTexture(GL_TEXTURE_2D, texture);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 64, 32, 0, GL_RGB, GL_FLOAT, texture_data);

  glBindVertexArray(vao);

  for (int i = 0; i<2048; i++) {
    texture_data[i] += 0.1;
  }
  
  // draw points 0-3 from the currently bound VAO with current in-use shader
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
  glBindVertexArray(0);

  glFlush();

  return false;
}

static void on_realize(GtkGLArea *area, GdkGLContext *context)
{

  // write out opengl version info
  print_opengl_info();

  gtk_gl_area_make_current(area);

  // buffers
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(points) * sizeof(float), points, GL_STATIC_DRAW);

  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, NULL);

  // define shaders
  const char *vertex_shader =
      "#version 400\n"
      "in vec3 vp;"
      "out vec2 Texcoord;"
      "void main() {"
      "  gl_Position = vec4(vp, 1.0);"
      "  Texcoord = vec2(vp.x, vp.y);"
      "}";

  const char *fragment_shader =
      "#version 400\n"
      "out vec4 frag_colour;"
      "in vec2 Texcoord;"
      "uniform sampler2D tex;"
      "void main() {"
      "  frag_colour = texture(tex, Texcoord);"
      "}";

  // compile shaders


  GLuint vs = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vs, 1, &vertex_shader, NULL);
  glCompileShader(vs);
  GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fs, 1, &fragment_shader, NULL);
  glCompileShader(fs);

  // attach to program
  shader_programme = glCreateProgram();
  glAttachShader(shader_programme, vs);
  glAttachShader(shader_programme, fs);
  glLinkProgram(shader_programme);

  // texture
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 64, 32, 0, GL_RGB, GL_FLOAT, texture_data);
};

GtkWidget *chip8_add_display(GtkWindow *window)
{
  GtkWidget *gl_area = gtk_gl_area_new();
  g_signal_connect(gl_area, "render", G_CALLBACK(on_render), NULL);
  g_signal_connect(gl_area, "realize", G_CALLBACK(on_realize), NULL);
  gtk_window_set_child(window, gl_area);
  return gl_area;
}