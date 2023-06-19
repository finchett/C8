#include "chip8_application.h"

struct _Chip8Application
{
    GtkApplication parent;
};

G_DEFINE_TYPE(Chip8Application, chip8_application, GTK_TYPE_APPLICATION)

static void chip8_application_class_init(Chip8ApplicationClass *class)
{
    return;
};

static void chip8_application_init(Chip8Application *instance)
{
    return;
};

// Managing window may not belong here.
static void activate (Chip8Application *app)
{
  GtkWidget *window;

  window = gtk_application_window_new (app);

  gtk_window_set_title (GTK_WINDOW (window), "Window");
  gtk_window_set_default_size (GTK_WINDOW (window), 400, 300);
  gtk_window_present (window);
};

Chip8Application *chip8_application_new()
{
    Chip8Application *instance;


    instance = g_object_new(CHIP8_TYPE_APPLICATION, 
                            "application-id", "com.github.sfinche.C8",
                            "flags", G_APPLICATION_HANDLES_OPEN, NULL);

    g_signal_connect(instance, "activate", G_CALLBACK (activate), NULL);

    return instance;
};
