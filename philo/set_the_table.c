#include "philo.h"


void    distribute_forks(t_philo *philo, t_fork *forks, int position)
{
    philo->left_fork = &forks[(position + 1) % philo->table->nbr_philos];
    philo->right_fork = &forks[position];
    if (philo->id % 2 == 0)
    {
        philo->left_fork = &forks[position];
        philo->right_fork = &forks[(position + 1) % philo->table->nbr_philos];
    }
}
// function to distribute forks in a circular manner
// for even numbered philos the distribution is reversed to avoid deadlock

void    set_philo(t_table *table)
{
    int i;

    i = 0;
    while (i < table->nbr_philos)
    {
        table->philos->id = i;
        table->philos->hungry = true;
        table->philos->meals_eaten = 0;
        table->philos->table = table;
        distribute_forks(table->philos, table->forks, i);
        i++;
    }
}

int    set_the_table(t_table *table)
{
    int i;

    i = 0;
    table->philo_died = false;
    table->philos = malloc(sizeof(t_philo) * (table->nbr_philos)); // NULL terminate?
    if (!table->philos)
        return (error_handling("table->philos", "allocation failure"), -1);
    table->forks = malloc(sizeof(t_fork) * table->nbr_philos);
    if (!table->forks)
        return (error_handling("table->forks", "allocation failure"), free(table->philos), -1);
    while (i < table->nbr_philos)
    {
        if (pthread_mutex_init(&table->forks[i].fork, NULL) != 0)
            return (error_handling(NULL, "Mutex init failed"), -1); // free philos and forks
        table->forks[i].fork_id = i;
        i++;
    }
    set_philo(table);
    return (0);
}

    // allocate philos
    // allocate forks
    // init mutex forks
        // forks are mutexes, which means they can only be accessed by one philo at a time
    // init philos
        // loop
        // philo id = i + 1
        // philo full = false
        // philo meals counter = 0
        // philo table = table
        // assign forks

