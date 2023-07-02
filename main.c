#include <gtk/gtk.h>
#include "chip8_application.h"
#include "chip8_window.h"
#include <stdio.h>
#include <epoxy/gl.h>


static void activate (GtkApplication *app)
{
  Chip8Window *window;
  window = chip8_window_new(app);

};

int main (int argc, char *argv[])
{
    GtkApplication *chip8;

    chip8 = g_object_new(GTK_TYPE_APPLICATION, "application-id",
                          "com.github.sfinche.C8", "flags",
                          G_APPLICATION_HANDLES_OPEN, NULL);
                          
    g_signal_connect(chip8, "activate", G_CALLBACK (activate), NULL);
    
    g_application_run(G_APPLICATION (chip8), argc, argv);

    g_object_unref(chip8);

    return 0;
}
