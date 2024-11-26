#include "philo.h"

void    *single_philo(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    wait_threads(philo->table);
    set_long(&philo->philo_mutex, &philo->last_meal, time_stamp(philo->table->start_time));
    handle_mutex_lock(&philo->table->table_mutex, LOCK);
    philo->table->ready_count++;
    handle_mutex_lock(&philo->table->table_mutex, UNLOCK);
    write_status(philo, "has taken a fork");
    while (!philo->table)
        usleep(200);
    return (NULL);
}
