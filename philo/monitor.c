
#include "philo.h"

bool    philo_died(t_philo *philo)
{
    long    elapsed_time;

    pthread_mutex_lock(&philo->philo_mutex);
    if (philo->full || get_bool(&philo->table->table_mutex, &philo->table->philo_died))
    {
        pthread_mutex_unlock(&philo->philo_mutex);
        return (false);
    }
    elapsed_time = time_stamp(philo->table->start_time);
    if (elapsed_time - philo->last_meal > philo->table->time_to_die)
    {
        philo->dead = true;
        pthread_mutex_unlock(&philo->philo_mutex);
        return (true);
    }
    pthread_mutex_unlock(&philo->philo_mutex);
    return (true);
}

bool    all_threads_running(t_table *table)
{
    pthread_mutex_lock(&table->table_mutex);
    // printf("all_threads_running ready_count: %d\n", table->ready_count);
    if (table->ready_count == table->nbr_philos)
    {
        pthread_mutex_unlock(&table->table_mutex);
        return (true);
    }
    pthread_mutex_unlock(&table->table_mutex);
    return (false);
}


void    *monitor_dinner(void *arg)
{
    t_table *table;
    // bool    all_full;
    int i;

    table = (t_table *)arg;
    printf("TEST\n");
    while (!all_threads_running(table))
        usleep(10);
    
    printf(MAGENTA"all threads are running\n"WHITE);
    while (!table->finished)
    {
        i = 0;
        while (i < table->nbr_philos)
        {
            if (philo_died(&table->philos[i]))
            {
                write_status(table->philos, "died");
                table->philo_died = true;
                break ;
            }
            i++;
        }

        usleep(1000);
    }
    return (NULL);
}


