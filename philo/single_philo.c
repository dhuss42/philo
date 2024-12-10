/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 14:50:33 by dhuss             #+#    #+#             */
/*   Updated: 2024/12/04 14:36:31 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*single_philo(void *arg)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)arg;
	table = philo->table;
	handle_mutex_lock(&table->table_mutex, LOCK);
	table->ready_count++;
	if (table->ready_count == table->nbr_philos)
	{
		table->threads_ready = true;
	}
	handle_mutex_lock(&table->table_mutex, UNLOCK);
	wait_threads(table);
	set_long(&philo->philo_mutex, &philo->last_meal,
		time_stamp(table->start_time));
	write_status(philo, "has taken a fork");
	while (!table)
		usleep(200);
	return (NULL);
}
