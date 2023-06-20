#include <gtk/gtk.h>
#include "chip8_window.h"
#include "chip8_application.h"


// c type first:
// then use convenience macro to register the type
// then define the class and instance init functions declared in the last step.

struct _Chip8Window {
    GtkApplicationWindow parent;
};

G_DEFINE_TYPE(Chip8Window, chip8_window, GTK_TYPE_APPLICATION_WINDOW)

static void chip8_window_class_init() {
    return;
};

static void chip8_window_init() {
    return;
};

Chip8Window *chip8_window_new (Chip8Application *app) {
    Chip8Window *instance;

    return g_object_new (CHIP8_TYPE_WINDOW, "application", app, NULL);
}
