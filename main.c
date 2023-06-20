#include <gtk/gtk.h>
#include "chip8_application.h"
#include "chip8_window.h"
#include <stdio.h>
#include <epoxy/gl.h>

// TODO: see https://www.bassi.io/articles/2015/02/17/using-opengl-with-gtk/ for program structure.


// static bool
// render (GtkGLArea *area, GdkGLContext *context)
// {
//   return False;
// }

// static void init_buffer_objects()
// {
// };

// static void realize (GtkGLArea *area, GdkGLContext *context)
// {
//   gtk_gl_area_make_current(area);
//   init_buffer_objects ();
// };

// // Managing window may not belong here.
static void activate (Chip8Application *app)
{
  Chip8Window *window;
  window = chip8_window_new(app);
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
