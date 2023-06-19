#include <gtk/gtk.h>
#include "chip8_application.h"
#include <stdio.h>
#include <epoxy/gl.h>

// TODO: see https://www.bassi.io/articles/2015/02/17/using-opengl-with-gtk/ for program structure.


static bool
render (GtkGLArea *area, GdkGLContext *context)
{
  return False;
}

static void init_buffer_objects()
{
};

static void realize (GtkGLArea *area, GdkGLContext *context)
{
  gtk_gl_area_make_current(area);
  init_buffer_objects ();
};

// Managing window may not belong here.
static void activate (Chip8Application *app)
{
  GtkWidget *window;

  window = gtk_application_window_new (GTK_APPLICATION (app));
  gtk_window_set_title (GTK_WINDOW (window), "Window");
  gtk_window_set_default_size (GTK_WINDOW (window), 400, 300);

  // create a GtkGLArea instance
  GtkWidget *gl_area = gtk_gl_area_new ();
  gtk_widget_set_visible(gl_area, TRUE);
  gtk_widget_set_can_focus(gl_area, FALSE);
  gtk_widget_set_hexpand(gl_area, TRUE);
  gtk_widget_set_vexpand(gl_area, TRUE);

  g_signal_connect (gl_area, "realize", G_CALLBACK (realize), NULL);
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

    return 0;
}
