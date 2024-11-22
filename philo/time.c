
#include "philo.h"

long time_stamp(long    start_time)
{
    struct timeval ts;
    long    elapsed_ms;

    if (gettimeofday(&ts, NULL) == -1)
    {
        // call error
    }
    elapsed_ms = ((ts.tv_sec) * 1000 + (ts.tv_usec) / 1000) - start_time;
    return (elapsed_ms);
}

void    set_start_time(t_table *table)
{
    struct timeval tv;

    if (gettimeofday(&tv, NULL) == -1)
    {
        // call error
    }
    table->start_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
    printf("start_time %ld\n", table->start_time);
}
//--------//
// gets time of day
// sets start time in ms in table struct
// later time_stamp function will take the start_time
// and subtract the current time to get the elapsed time