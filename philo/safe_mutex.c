
#include "philo.h"

void    handle_mutex_lock(t_mtx *mutex, int router)
{
    if (router == LOCK)
    {
        if (pthread_mutex_lock(mutex) != 0)
            return (error_handling("mutex", "lock error"));
    }
    else if (router == UNLOCK)
    {
        if (pthread_mutex_unlock(mutex) != 0)
            return (error_handling("mutex", "unlock error"));
    }
}
