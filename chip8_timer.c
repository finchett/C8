#include "chip8_timer.h"
#include "stdio.h"

/* 17ms between ticks ~= 60/s*/
const int rate = 17;

/*
    todo: move rate into chip8 timer.
        setter will call g_timeout remove and g_timeout_add.
*/ 

struct _Chip8Timer {
    GObject parent;
    u_int8_t tick;
    guint on_tick_signal_id;
};

G_DEFINE_TYPE(Chip8Timer, chip8_timer, G_TYPE_OBJECT)

static void chip8_decrement_timer(gpointer data) {
    Chip8Timer *timer = data;
    
    g_signal_emit(timer, timer->on_tick_signal_id, 0, NULL);
    
    timer->tick--;
    return;
}

static void chip8_timer_class_init(Chip8TimerClass *class) {
    return;
};


static void chip8_timer_init(Chip8Timer *instance) {

    instance->on_tick_signal_id = g_signal_new("on_tick", CHIP8_TYPE_TIMER, G_SIGNAL_RUN_LAST,
         0, NULL, NULL, NULL, G_TYPE_NONE, 0);

    g_timeout_add(rate, (GSourceFunc) chip8_decrement_timer, (gpointer) instance );
    return;
}

Chip8Timer *chip8_timer_new() {
    return g_object_new(CHIP8_TYPE_TIMER, "tick", (u_int8_t) 255);
}


