#include <gtk/gtk.h>
GHashTable *mappings;

int16_t chip8_input[16];

/*
  mappings are stored in hashmap offset by one so that 0x0 can be used for X. unmapped keys return -1.
*/

static bool set_mapping(int key, int val) {
  return g_hash_table_insert(mappings, GINT_TO_POINTER (key), GINT_TO_POINTER (val + 1));
}

static int16_t get_mapping(int keyval) {
  gpointer p = g_hash_table_lookup(mappings, GINT_TO_POINTER(keyval));
  if (p == NULL) {
    return -1;
  } else {
    return (GPOINTER_TO_INT (p) - 1);
  }
}

static gboolean key_pressed(
    GtkEventControllerKey *self,
    guint keyval,
    guint keycode,
    GdkModifierType *state,
    gpointer user_data)
{
  keyval = gdk_keyval_to_upper(keyval);

  int16_t chip8_button = get_mapping(keyval);
  chip8_input[chip8_button] = true;
}

static void key_released (
  GtkEventControllerKey* self,
  guint keyval,
  guint keycode,
  GdkModifierType* state,
  gpointer user_data) 
{
  keyval = gdk_keyval_to_upper(keyval);

  int16_t chip8_button = get_mapping(keyval);
  chip8_input[chip8_button] = false;
}

int16_t *chip8_add_keyboard_input(GtkWidget *window)
{
    mappings = g_hash_table_new(g_direct_hash, g_direct_equal);

    set_mapping(GDK_KEY_1, 0x1);
    set_mapping(GDK_KEY_2, 0x2);
    set_mapping(GDK_KEY_3, 0x3);
    set_mapping(GDK_KEY_4, 0xC);

    set_mapping(GDK_KEY_Q, 0x4);
    set_mapping(GDK_KEY_W, 0x5);
    set_mapping(GDK_KEY_E, 0x6);
    set_mapping(GDK_KEY_R, 0xD);

    set_mapping(GDK_KEY_A, 0x7);
    set_mapping(GDK_KEY_S, 0x8);
    set_mapping(GDK_KEY_D, 0x9);
    set_mapping(GDK_KEY_F, 0xE);

    set_mapping(GDK_KEY_Z, 0xA);
    set_mapping(GDK_KEY_X, 0x0);
    set_mapping(GDK_KEY_C, 0xB);
    set_mapping(GDK_KEY_V, 0xF);

    GtkEventController *controller = gtk_event_controller_key_new();

    g_signal_connect(controller, "key-pressed", key_pressed, NULL);
    g_signal_connect(controller, "key-released", key_released, NULL);

    gtk_widget_add_controller(window, controller);

    return chip8_input;
}
