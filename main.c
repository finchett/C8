#include <gtk/gtk.h>
#include "chip8_application.h"
#include <stdio.h>

int main (int argc, char *argv[])
{
    Chip8Application *chip8;
    chip8 = chip8_application_new();



    g_object_unref (chip8);

    return 0;
}
