/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 10:08:19 by dhuss             #+#    #+#             */
/*   Updated: 2024/11/25 14:59:06 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

bool	philo_died(t_philo *philo)
{
	long	elapsed_time;

	// printf(GREEN"philo mutex lock in philo died\n"WHITE);
	pthread_mutex_lock(&philo->philo_mutex); // table, philo mutex locked
	if (philo->full/*  || get_bool(&philo->table->table_mutex, &philo->table->philo_died) */)
	{
		// printf("TEst1\n");

		pthread_mutex_unlock(&philo->philo_mutex); // table locked / philo unlocked
		// printf(YELLOW"philo mutex unlock in philo died\n"WHITE);
		return (false);
	}
	elapsed_time = time_stamp(philo->table->start_time);
	// printf(CYAN"elapsed_time %ld\n", elapsed_time);
	// printf(CYAN"philo last meal %ld\n", philo->last_meal);
	// printf(CYAN"time to die %ld\n", philo->table->time_to_die / 1000);
	// printf(CYAN"%ld - %ld > %ld\n"WHITE, elapsed_time, philo->last_meal, philo->table->time_to_die / 1000);
	if (elapsed_time - philo->last_meal > philo->table->time_to_die / 1000)
	{
		printf(MAGENTA"TEST\n"WHITE);
		philo->dead = true;
		pthread_mutex_unlock(&philo->philo_mutex); // table locked / philo unlocked
		// printf(YELLOW"philo mutex unlock in philo died\n"WHITE);
		return (true);
	}
	// printf("TEst2\n");
	pthread_mutex_unlock(&philo->philo_mutex); // table locked / philo unlocked
	// printf(YELLOW"philo mutex unlock in philo died\n"WHITE);
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
	// bool	all_full;
	int i;

	table = (t_table *)arg;
	printf(MAGENTA"created monitor\n"WHITE);
	while (!all_threads_running(table))
		usleep(10);

	printf(MAGENTA"all threads are running\n"WHITE);
	while (!table->finished)
	{
		i = 0;
		while (i < table->nbr_philos)
		{

			pthread_mutex_lock(&table->table_mutex); // table mutex locked
			if (philo_died(&table->philos[i]))
			{
				printf(MAGENTA"TEST2\n"WHITE);
				write_status(table->philos, "died");
				pthread_mutex_unlock(&table->table_mutex); // table unlocked
				return (NULL) ; // maybe return?
			}
			pthread_mutex_unlock(&table->table_mutex); // table unlocked
			if (get_bool(&table->philos->philo_mutex, &table->philos->full) == true)
			{
				printf("philo is full\n");
				return (NULL);
			}
			i++;
		}
		// exit(EXIT_SUCCESS);
		usleep(10);
	}
	return (NULL);
}


