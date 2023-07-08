#include "chip8_timer.h"
#include "stdio.h"

/* 17ms between ticks ~= 60/s*/

/*
    todo: move rate into chip8 timer.
        setter will call g_timeout remove and g_timeout_add.
*/

typedef enum
{
    PROP_TICK = 1,
    PROP_RATE,
    N_PROPERTIES
} Chip8TimerProperty;

static GParamSpec *timer_properties[N_PROPERTIES] = {
    NULL,
};

enum
{
    ON_TICK,
    NUM_SIGNALS
};

static guint signals[NUM_SIGNALS] = {0};

G_DEFINE_TYPE(Chip8Timer, chip8_timer, G_TYPE_OBJECT)

static void chip8_decrement_timer(gpointer data)
{
    Chip8Timer *timer = data;

    g_signal_emit(timer, signals[ON_TICK], 0, NULL);

    timer->tick--;
    return;
}

static void chip8_timer_set_property(GObject *object, guint property_id, const GValue *value, GParamSpec *pspec)
{
    Chip8Timer *self = CHIP8_TIMER(object);

    switch (property_id)
    {
        case PROP_TICK:
            self->tick = g_value_get_uint(value);
            break;
        case PROP_RATE:
            self->rate = g_value_get_int(value);
            break;
        default:
            G_OBJECT_WARN_INVALID_PROPERTY_ID(object, property_id, pspec);
    }

};

static void chip8_timer_get_property(GObject *object, guint property_id, GValue *value, GParamSpec *pspec)
{
    Chip8Timer *self = CHIP8_TIMER(object);

 switch (property_id)
    {
        case PROP_TICK:
            g_value_set_uint(value, self->tick);
            break;
        case PROP_RATE:
            g_value_set_int(value, self->rate);
            break;
        default:
            G_OBJECT_WARN_INVALID_PROPERTY_ID(object, property_id, pspec);
    }
};

static void chip8_timer_class_init(Chip8TimerClass *class)
{

    GObjectClass *object_class = G_OBJECT_CLASS(class);

    object_class->set_property = chip8_timer_set_property;
    object_class->get_property = chip8_timer_get_property;

    timer_properties[PROP_TICK] =
        g_param_spec_uint("tick",
                          "Tick",
                          "Starting value for the timer.",
                          0 /* minimum value */,
                          255 /* maximum value */,
                          255 /* default value */,
                          G_PARAM_READWRITE);

    timer_properties[PROP_RATE] =
        g_param_spec_int("rate",
                          "Rick",
                          "timer frequency in hertz.",
                          0 /* minimum value */,
                          1000 /* maximum value */,
                          17 /* default value */,
                          G_PARAM_READWRITE);                          

    g_object_class_install_properties(object_class, N_PROPERTIES, timer_properties);
};

static void chip8_timer_init(Chip8Timer *instance)
{

    signals[ON_TICK] = g_signal_new("on_tick", CHIP8_TYPE_TIMER, G_SIGNAL_RUN_LAST,
                                    0, NULL, NULL, NULL, G_TYPE_NONE, 0);


    // TODO: time constructor using properties.
    // test multiple timers can be created.
    g_timeout_add(17, (GSourceFunc)chip8_decrement_timer, (gpointer)instance);
    return;
}

Chip8Timer *chip8_timer_new(uint8_t tick, int rate)
{
    return g_object_new(CHIP8_TYPE_TIMER, "tick", tick, "rate", rate, NULL);
}
