#include <gtk/gtk.h>
#include "chip8_application.h"
#include "chip8_window.h"
#include "chip8_timer.h"
#include <stdio.h>
#include <epoxy/gl.h>

static void activate (Chip8Application *app)
{
  Chip8Window *window;
  Chip8Timer *timer;
  window = chip8_window_new(app);
  timer = chip8_timer_new();
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
