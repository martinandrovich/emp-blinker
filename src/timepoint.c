extern TIMEPOINT * new_TIMEPOINT(UINT32U clock_freq, UINT32U systick_dur)
{
    TIMEPOINT * tp = malloc(sizeof(TIMEPOINT));
    return tp;
}

void TIMEPOINT * del_TIMEPOINT(TIMEPOINT * tp )
{
    free(tp);
}
