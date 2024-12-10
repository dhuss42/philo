/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 10:05:34 by dhuss             #+#    #+#             */
/*   Updated: 2024/12/03 15:21:31 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	cleaner(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nbr_philos)
	{
		if (pthread_mutex_destroy(&table->philos[i].philo_mutex) != 0) // check with hellgrind
			error("DESTROY", E_MUTEX);
		if (pthread_mutex_destroy(&table->forks[i].fork) != 0) // here too
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
