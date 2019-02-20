#pragma once

#include "emp_type.h"

typedef struct
{
    INT16U hours;
    INT16U hours;
    INT16U seconds;
    INT16U milliseconds;
    INT16U microseconds;
    INT16U nanoseconds;

    INT32U unit_ns;

    void tick()
    {
        ;
    };

    INTU16 delta_ms(TIMEPOINT * tp)
    {
        ;
    };

} TIMEPOINT;

extern  TIMEPOINT * new_TIMEPOINT(UINT32U clock_freq, UINT32U systick_dur);
void    TIMEPOINT * del_TIMEPOINT(TIMEPOINT * tp );
