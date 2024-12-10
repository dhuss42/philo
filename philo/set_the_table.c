/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_the_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 12:06:56 by dhuss             #+#    #+#             */
/*   Updated: 2024/12/04 14:35:50 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	distribute_forks(t_philo *philo, t_fork *forks, int position)
{
	philo->left_fork = &forks[position];
	philo->right_fork = &forks[(position + 1) % philo->table->nbr_philos];
}

void	set_philo(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nbr_philos)
	{
		table->philos[i].id = i + 1;
		table->philos[i].full = false;
		table->philos[i].meals_eaten = 0;
		table->philos[i].table = table;
		table->philos[i].dead = false;
		table->philos[i].last_meal = table->time_to_eat;
		if (pthread_mutex_init(&table->philos[i].philo_mutex, NULL) != 0)
			error(NULL, E_MUTEX);
		distribute_forks(&table->philos[i], table->forks, i);
		i++;
	}
}

void	init_table_struct(t_table *table)
{
	table->philo_died = false;
	table->threads_ready = false;
	table->finished = false;
	table->ready_count = 0;
	table->full_count = 0;
	table->start_time = 0;
}

int	set_the_table(t_table *table)
{
	int	i;

	init_table_struct(table);
	i = 0;
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
			return (error(NULL, E_MUTEX), -1);
		table->forks[i].fork_id = i;
		i++;
	}
	set_philo(table);
	return (0);
}
