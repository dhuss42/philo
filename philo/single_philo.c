#include "philo.h"

void    *single_philo(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    handle_mutex_lock(&philo->table->table_mutex, LOCK);
    philo->table->ready_count++;
    if (philo->table->ready_count == philo->table->nbr_philos)
    {
        philo->table->threads_ready = true;
    }
    handle_mutex_lock(&philo->table->table_mutex, UNLOCK);
    wait_threads(philo->table);
    set_long(&philo->philo_mutex, &philo->last_meal, time_stamp(philo->table->start_time));
    write_status(philo, "has taken a fork");
    while (!philo->table)
        usleep(200);
    return (NULL);
}

// single philo
// increment ready count
// set ready to true
// set last meal time
// write status simulating taking a fork
// wait till monitor catches him