#include "philo.h"


void    cleaner(t_table *table)
{
    int i;

    i = 0;
    while (i < table->nbr_philos)
    {
        if (pthread_mutex_destroy(&table->philos[i].philo_mutex) != 0)
            error("DESTROY", E_MUTEX);
        if (pthread_mutex_destroy(&table->forks[i].fork) != 0)
            error("DESTROY", E_MUTEX);
        i++;
    }
    if (pthread_mutex_destroy(&table->table_mutex) != 0)
        error("DESTROY", E_MUTEX);
    if (pthread_mutex_destroy(&table->write_mutex) != 0)
        error("DESTROY", E_MUTEX);
    if (table->forks)
        free(table->forks);
    if (table->philos)
        free(table->philos);
}
// free philos
// loop through nbr of philos
//      philo = table->philo + i
//      destory philo_mutex
// destroy table write_mutex
// destroy Table_mutex
// free forks
// free philos