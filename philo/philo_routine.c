/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 10:08:26 by dhuss             #+#    #+#             */
/*   Updated: 2024/11/25 14:40:24 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_status(t_philo *philo, const char *status)
{
	long elapsed_time;

	// check with table simulation
	handle_mutex_lock(&philo->philo_mutex, LOCK);
	if (philo->dead == true || philo->full == true)
	{
		printf(RED"Philo is full or dead\n"WHITE);
		handle_mutex_lock(&philo->philo_mutex, UNLOCK);
		return ;
	}
	handle_mutex_lock(&philo->philo_mutex, UNLOCK);
	// printf(GREEN"locking philo mutex in write_status\n"WHITE);
	handle_mutex_lock(&philo->table->table_mutex, LOCK);
	elapsed_time = time_stamp(philo->table->start_time);
	handle_mutex_lock(&philo->table->table_mutex, UNLOCK);
	
	// printf(YELLOW"unlock philo mutex in write_status\n"WHITE);

	// printf(YELLOW"locking write mutex\n"WHITE);
	pthread_mutex_lock(&philo->table->write_mutex);
	printf("%ld %d %s\n", elapsed_time, philo->id, status);
	pthread_mutex_unlock(&philo->table->write_mutex);
	// printf(GREEN"unlocking write mutex\n"WHITE);
}

//-------------------------//
// checks if the philo is full or if a philo died
//	  prints according message
//		  ----> not sure if the message should be printed here
// gets time passed since start
// prints status message that was passed as arg


void	eat(t_philo *philo)
{
	handle_mutex_lock(&philo->philo_mutex, LOCK);
	if (philo->dead == true || philo->full == true)
	{
		printf(RED"Philo is full or dead\n"WHITE);
		handle_mutex_lock(&philo->philo_mutex, UNLOCK);
		return ;
	}
	handle_mutex_lock(&philo->philo_mutex, UNLOCK);
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

	handle_mutex_lock(&philo->philo_mutex, LOCK);
	philo->last_meal = time_stamp(philo->table->start_time);
	philo->meals_eaten++;
	handle_mutex_lock(&philo->philo_mutex, UNLOCK);

	write_status(philo, "is eating");
	custom_usleep(philo->table->time_to_eat / 1000, philo->table);
	handle_mutex_lock(&philo->right_fork->fork, UNLOCK);
	handle_mutex_lock(&philo->left_fork->fork, UNLOCK);

	handle_mutex_lock(&philo->philo_mutex, LOCK);
	if (philo->meals_eaten == philo->table->nbr_meals)
	{
		philo->full = true; // increment counter
	}
	handle_mutex_lock(&philo->philo_mutex, UNLOCK);
}

//-------------------------//
// if the philo id is even it takes the left fork and then the right fork
// if the philo id is odd it takes the right fork and then the left fork
// updates the last_meal time of the philo to the current time - start-time
// ----> I think this is not correct
// increaments meals_eaten inside mutex
// waits until time to eat is over
// if meals eaten is = nbr of meals
//  set philo full to true;


void	custom_sleep(t_philo *philo)
{
	// t_table *table;

	handle_mutex_lock(&philo->philo_mutex, LOCK);
	if (philo->dead == true || philo->full == true)
	{
		printf(RED"Philo is full or dead\n"WHITE);
		handle_mutex_lock(&philo->philo_mutex, UNLOCK);
		return ;
	}
	handle_mutex_lock(&philo->philo_mutex, UNLOCK);
	// table = philo->table;
	write_status(philo, "is sleeping");
	// long start_sleep = time_stamp(table->start_time);
	custom_usleep(philo->table->time_to_sleep / 1000, philo->table);
	// long end_sleep = time_stamp(table->start_time);
	// printf("Philosoper %d slept for %ld ms\n", philo->id, end_sleep - start_sleep);
}

// wirtes status sleeping
// sleeps for time_to_sleep

//------custom usleep------//
// 1:20

void	think(t_philo *philo)
{
	t_table *table;
	long	think_time;

	handle_mutex_lock(&philo->philo_mutex, LOCK);
	if (philo->dead == true || philo->full == true)
	{
		printf(RED"Philo is full or dead\n"WHITE);
		handle_mutex_lock(&philo->philo_mutex, UNLOCK);
		return ;
	}
	handle_mutex_lock(&philo->philo_mutex, UNLOCK);
	table = philo->table;
	write_status(philo, "is thinking");
	if (table->nbr_philos % 2 == 0)
		return ;
	think_time = (table->time_to_eat * 2) - table->time_to_sleep;
	if (think_time < 0)
		think_time = 0;
	custom_usleep((think_time / 1000) * 0.5, philo->table);
	// printf("Philosopher %d thought for %ld ms\n", philo->id, think_time);
}

// writes status is thinking
// if philo_nbr is even the function returns
// ---> an even numbered simulation is in itself fait
// if not even has to think long
// ---> need to look up why this length

