/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 10:08:26 by dhuss             #+#    #+#             */
/*   Updated: 2024/12/06 11:56:43 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_status(t_philo *philo, const char *status)
{
	long	elapsed_time;

	if (get_bool(&philo->table->table_mutex, &philo->table->finished))
		return ;
	handle_mutex_lock(&philo->table->table_mutex, LOCK);
	elapsed_time = time_stamp(philo->table->start_time);
	handle_mutex_lock(&philo->table->table_mutex, UNLOCK);
	pthread_mutex_lock(&philo->table->write_mutex);
	printf("%ld %d %s\n", elapsed_time, philo->id, status);
	pthread_mutex_unlock(&philo->table->write_mutex);
}

void	grabbing_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		handle_mutex_lock(&philo->left_fork->fork, LOCK);
		write_status(philo, "has taken a fork");
		handle_mutex_lock(&philo->right_fork->fork, LOCK);
		write_status(philo, "has taken a fork");
	}
	else
	{
		handle_mutex_lock(&philo->right_fork->fork, LOCK);
		write_status(philo, "has taken a fork");
		handle_mutex_lock(&philo->left_fork->fork, LOCK);
		write_status(philo, "has taken a fork");
	}
}

void	eat(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	if (health_check(philo) == -1)
		return ;
	handle_mutex_lock(&table->table_mutex, LOCK);
	if (table->full_count == table->nbr_philos)
	{
		handle_mutex_lock(&table->table_mutex, UNLOCK);
		return ;
	}
	handle_mutex_lock(&table->table_mutex, UNLOCK);
	grabbing_forks(philo);
	handle_mutex_lock(&philo->philo_mutex, LOCK);
	philo->last_meal = time_stamp(philo->table->start_time);
	handle_mutex_lock(&philo->philo_mutex, UNLOCK);
	write_status(philo, "is eating");
	custom_usleep(philo->table->time_to_eat / 1000, philo->table);
	increment_int(&philo->philo_mutex, (int *)&philo->meals_eaten);
	handle_mutex_lock(&philo->right_fork->fork, UNLOCK);
	handle_mutex_lock(&philo->left_fork->fork, UNLOCK);
	full_check(philo);
}

void	custom_sleep(t_philo *philo)
{
	if (health_check(philo) == -1)
		return ;
	write_status(philo, "is sleeping");
	custom_usleep(philo->table->time_to_sleep / 1000, philo->table);
}

void	think(t_philo *philo)
{
	t_table	*table;
	long	think_time;

	if (health_check(philo) == -1)
		return ;
	table = philo->table;
	write_status(philo, "is thinking");
	if (table->nbr_philos % 2 == 0)
		return ;
	think_time = (table->time_to_eat * 2) - table->time_to_sleep;
	if (think_time < 0)
		think_time = 0;
	custom_usleep((think_time / 1000) * 0.5, table);
}
