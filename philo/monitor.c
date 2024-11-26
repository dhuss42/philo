/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 10:08:19 by dhuss             #+#    #+#             */
/*   Updated: 2024/11/25 16:09:10 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

bool	philo_died(t_philo *philo)
{
	long	elapsed_time;

	handle_mutex_lock(&philo->table->table_mutex, LOCK);
	elapsed_time = time_stamp(philo->table->start_time);
	handle_mutex_lock(&philo->table->table_mutex, UNLOCK);

	pthread_mutex_lock(&philo->philo_mutex); 
	if (philo->full)
	{
		pthread_mutex_unlock(&philo->philo_mutex);
		return (false);
	}
	if (elapsed_time - philo->last_meal > philo->table->time_to_die / 1000)
	{
		// printf(MAGENTA"philo died\n"WHITE);
		philo->dead = true;
		pthread_mutex_unlock(&philo->philo_mutex);
		return (true);
	}
	pthread_mutex_unlock(&philo->philo_mutex);
	return (false);
}

bool	all_threads_running(t_table *table)
{
	pthread_mutex_lock(&table->table_mutex);
	// printf("monitor: adress table %p\n", table);
	// printf("all_threads_running ready_count: %d\n", table->ready_count);
	if (table->threads_ready == true)
	{
		pthread_mutex_unlock(&table->table_mutex);
		return (true);
	}
	pthread_mutex_unlock(&table->table_mutex);
	// exit(EXIT_SUCCESS);
	return (false);
}


void	*monitor_dinner(void *arg)
{
	t_table *table;
	int i;

	table = (t_table *)arg;
	while (!all_threads_running(table))
		usleep(10);

	while (!table->finished)
	{
		i = 0;
		while (i < table->nbr_philos)
		{
			if (philo_died(&table->philos[i]))
			{
				write_status(table->philos, "died");
				set_bool(&table->table_mutex, &table->finished, true);
			}
			if (get_bool(&table->philos->philo_mutex, &table->philos->full) == true)
			{
				set_bool(&table->table_mutex, &table->finished, true);
			}
			i++;
		}
		usleep(10);
	}
	return (NULL);
}


