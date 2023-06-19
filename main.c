#include <gtk/gtk.h>
#include "chip8_application.h"
#include <stdio.h>
#include <GL/glew.h>

static bool
render (GtkGLArea *area, GdkGLContext *context)
{
  // inside this function it's safe to use GL; the given
  // GdkGLContext has been made current to the drawable
  // surface used by the `GtkGLArea` and the viewport has
  // already been set to be the size of the allocation

  // we can start by clearing the buffer
  // coloring to check if working.
  glClearColor (90, 0, 0, 0);
  glClear (GL_COLOR_BUFFER_BIT);
  
  // we completed our drawing; the draw commands will be
  // flushed at the end of the signal emission chain, and
  // the buffers will be drawn on the window
  return TRUE;
}

// Managing window may not belong here.
static void activate (Chip8Application *app)
{
  GtkWidget *window;


  window = gtk_application_window_new (GTK_APPLICATION (app));
  gtk_window_set_title (GTK_WINDOW (window), "Window");
  gtk_window_set_default_size (GTK_WINDOW (window), 400, 300);


  // create a GtkGLArea instance
  GtkWidget *gl_area = gtk_gl_area_new ();
  g_signal_connect (gl_area, "render", G_CALLBACK (render), NULL);
  gtk_window_set_child(GTK_WINDOW(window), gl_area);

  gtk_window_present (GTK_WINDOW (window));

};

int main (int argc, char *argv[])
{
    Chip8Application *chip8;
    chip8 = chip8_application_new();
    
    g_signal_connect(chip8, "activate", G_CALLBACK (activate), NULL);

    g_application_run(G_APPLICATION (chip8), argc, argv);


    g_object_unref(chip8);

    
    /*
    
    todo: refactore for readability.
      - makes app

      - attach activate signal that will:
        - make window
        - make widget
        - connect signals

      - run
    
    */

    return 0;
}
