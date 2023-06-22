#include "chip8_timer.h"
#include "stdio.h"

struct _Chip8Timer {
    GObject parent;
    u_int8_t tick;
};

G_DEFINE_TYPE(Chip8Timer, chip8_timer, G_TYPE_OBJECT)

static void chip8_decrement_timer_callback(gpointer data) {
    Chip8Timer *timer = data;
    timer->tick--;
    return;
}

static void chip8_timer_class_init(Chip8TimerClass *class) {
    return;
};


static void chip8_timer_init(Chip8Timer *instance) {
    g_timeout_add(17, (GSourceFunc) chip8_decrement_timer_callback, (gpointer) instance );
    return;
}

Chip8Timer *chip8_timer_new() {
    return g_object_new(CHIP8_TYPE_TIMER, "tick", (u_int8_t) 255);
}


