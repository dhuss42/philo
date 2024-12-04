/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:47:42 by dhuss             #+#    #+#             */
/*   Updated: 2024/12/04 14:47:47 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	full_check(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	handle_mutex_lock(&philo->philo_mutex, LOCK);
	if (philo->meals_eaten == table->nbr_meals)
	{
		philo->full = true;
	}
	handle_mutex_lock(&philo->philo_mutex, UNLOCK);
	if (get_bool(&philo->philo_mutex, &philo->full))
		increment_int(&table->table_mutex, &table->full_count);
}

int	health_check(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	if (get_bool(&table->table_mutex, &table->finished))
		return (-1);
	handle_mutex_lock(&philo->philo_mutex, LOCK);
	if (philo->dead == true)
	{
		handle_mutex_lock(&philo->philo_mutex, UNLOCK);
		return (-1);
	}
	handle_mutex_lock(&philo->philo_mutex, UNLOCK);
	return (0);
}
