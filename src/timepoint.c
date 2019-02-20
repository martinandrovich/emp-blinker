#include "timepoint.h"

void TIMEPOINT_tick(TIMEPOINT *self)
{
    ;
};

TIMEPOINT * new_TIMEPOINT(INT32U clock_freq, INT32U systick_dur)
{
    // allocate object
    TIMEPOINT * tp = malloc(sizeof(TIMEPOINT));

    // define default values
    tp->hours           = 0;
    tp->minutes         = 0;
    tp->seconds         = 0;
    tp->milliseconds    = 0;
    tp->microseconds    = 0;
    tp->nanoseconds     = 0;

    tp->tick = &TIMEPOINT_tick;

    return tp;
};

void del_TIMEPOINT(TIMEPOINT * tp )
{
    free(tp);
};
