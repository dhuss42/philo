/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_the_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 12:06:56 by dhuss             #+#    #+#             */
/*   Updated: 2024/11/25 14:46:42 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	distribute_forks(t_philo *philo, t_fork *forks, int position)
{
    philo->left_fork = &forks[position];
    philo->right_fork = &forks[(position + 1) % philo->table->nbr_philos];
    if (philo->id % 2 == 0)
    {
        philo->left_fork = &forks[position];
        philo->right_fork = &forks[(position + 1) % philo->table->nbr_philos];
    }
    printf("Philosopher %d assigned forks: Left = %d, Right = %d\n",
           philo->id, philo->left_fork->fork_id, philo->right_fork->fork_id);
}
// function to distribute forks in a circular manner
// for even numbered philos the distribution is reversed to avoid deadlock

void	set_philo(t_table *table)
{
	int i;

    i = 0;
    while (i < table->nbr_philos)
    {
        table->philos[i].id = i;
        table->philos[i].full = false;
        table->philos[i].meals_eaten = 0;
        table->philos[i].table = table;
        table->philo_died = false;
		table->philos[i].last_meal = table->time_to_eat / 1000;
        if (pthread_mutex_init(&table->philos[i].philo_mutex, NULL) != 0)
            error(NULL, E_MUTEX);
        distribute_forks(&table->philos[i], table->forks, i);
        i++;
    }
}

int	set_the_table(t_table *table)
{
	int i;

    i = 0;
    table->philo_died = false;
    table->threads_ready = false;
    table->ready_count = 0;
    table->finished = false;
    table->start_time = 0;
    table->philos = malloc(sizeof(t_philo) * (table->nbr_philos));
    if (!table->philos)
        return (error(NULL, E_ALLOC), -1);
    if (pthread_mutex_init(&table->table_mutex, NULL) != 0)
        return (error(NULL, E_MUTEX), -1);
    if (pthread_mutex_init(&table->write_mutex, NULL) != 0)
        return (error(NULL, E_MUTEX), -1);
    table->forks = malloc(sizeof(t_fork) * table->nbr_philos);
    if (!table->forks)
        return (error(NULL, E_ALLOC), -1);
    while (i < table->nbr_philos)
    {
        if (pthread_mutex_init(&table->forks[i].fork, NULL) != 0)
            return (error(NULL, E_MUTEX), -1); // free philos and forks
        table->forks[i].fork_id = i;
        i++;
    }
    set_philo(table); // possibly check for return value depends on how I handle inside the error function
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

