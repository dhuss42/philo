/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 10:08:19 by dhuss             #+#    #+#             */
/*   Updated: 2024/12/04 14:33:51 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	philo_died(t_philo *philo)
{
	long	elapsed_time;

	handle_mutex_lock(&philo->table->table_mutex, LOCK);
	elapsed_time = time_stamp(philo->table->start_time);
	handle_mutex_lock(&philo->table->table_mutex, UNLOCK);
	handle_mutex_lock(&philo->philo_mutex, LOCK);
	if (elapsed_time - philo->last_meal >= philo->table->time_to_die)
	{
		philo->dead = true;
		handle_mutex_lock(&philo->philo_mutex, UNLOCK);
		return (true);
	}
	if (philo->full)
	{
		handle_mutex_lock(&philo->philo_mutex, UNLOCK);
		return (false);
	}
	handle_mutex_lock(&philo->philo_mutex, UNLOCK);
	return (false);
}

bool	all_threads_running(t_table *table)
{
	handle_mutex_lock(&table->table_mutex, LOCK);
	if (table->threads_ready == true)
	{
		handle_mutex_lock(&table->table_mutex, UNLOCK);
		return (true);
	}
	handle_mutex_lock(&table->table_mutex, UNLOCK);
	return (false);
}

void	dead_or_full(t_table *table, int *i)
{
	if (philo_died(&table->philos[(*i)]))
	{
		if (table->nbr_philos > 150)
			if (table->nbr_philos % 2 != 0)
				usleep(6500);
			else
				usleep(2000);
		else
			usleep(1000);
		write_status(&table->philos[(*i)], "died");
		set_bool(&table->table_mutex, &table->finished, true);
	}
	handle_mutex_lock(&table->table_mutex, LOCK);
	if (table->full_count == table->nbr_philos)
		table->finished = true;
	handle_mutex_lock(&table->table_mutex, UNLOCK);
	(*i)++;
}

void	*monitor_dinner(void *arg)
{
	t_table	*table;
	int		i;

	table = (t_table *)arg;
	while (!all_threads_running(table))
		usleep(10);
	while (!table->finished)
	{
		i = 0;
		while (i < table->nbr_philos)
		{
			dead_or_full(table, &i);
		}
		usleep(5);
	}
	return (NULL);
}
