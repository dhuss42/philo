/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 12:45:19 by dhuss             #+#    #+#             */
/*   Updated: 2024/12/04 15:14:16 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_threads(t_table *table)
{
	while (!get_bool(&table->table_mutex, &table->threads_ready))
		usleep(10);
}

void	desync(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	if (table->nbr_philos % 2 == 0)
	{
		if (philo->id % 2 == 0)
			custom_usleep(30, philo->table);
	}
	else
	{
		if (philo->id % 2 == 0)
			think(philo);
	}
}

//------------//
// checks if the total amount of philos is even
//	if so it checks whether the current philo has an even position
//	  if so it sleeps
// if the total amount of philos is uneven
//	 the even numbered philos think first
//---> to make the simulation fair

void	*spagethi_time(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	handle_mutex_lock(&philo->table->table_mutex, LOCK);
	philo->table->ready_count++;
	if (philo->table->ready_count == philo->table->nbr_philos)
	{
		philo->table->threads_ready = true;
	}
	handle_mutex_lock(&philo->table->table_mutex, UNLOCK);
	wait_threads(philo->table);
	desync(philo);
	while (!get_bool(&philo->table->table_mutex, &philo->table->finished))
	{
		if (get_bool(&philo->philo_mutex, &philo->full))
			break ;
		if (get_bool(&philo->philo_mutex, &philo->dead))
			break ;
		eat(philo);
		custom_sleep(philo);
		think(philo);
	}
	return (NULL);
}

//---------//
// philo threads run through this function
// threads wait until all threads are ready
//	  lock mutex, add to counter,
//	  if counter = nbr of philos -> threads_ready true
//	  unlock mutex
//	  calls threads wait until threads_ready is set to true
// calls desync threads
//
// loop through routine until a philo is dead
//	  if a philo has eaten nbr_meals times break;
//	  calls eat
//	  calls sleep
//	  calls think

int	create_philos(t_table *table)
{
	int	i;

	i = 0;
	if (table->nbr_meals <= 0)
		return (error("nbr of meals", E_INVALIDINPT), -1);
	else if (table->nbr_philos == 1)
	{
		if (pthread_create(&table->philos[0].thread_id, NULL,
				single_philo, &table->philos[0]) != 0)
			return (error(NULL, E_PTHREAD), -1);
	}
	else
	{
		while (i < table->nbr_philos)
		{
			table->philos[i].table = table;
			if (pthread_create(&table->philos[i].thread_id, NULL,
					spagethi_time, &table->philos[i]) != 0)
				return (error(NULL, E_PTHREAD), -1);
			i++;
		}
	}
	return (0);
}

int	dinner(t_table *table)
{
	int	j;

	j = 0;
	if (set_start_time(table) == -1)
		return (-1);
	if (create_philos(table) == -1)
		return (-1);
	if (pthread_create(&table->doctor, NULL, monitor_dinner, table) != 0)
		return (error(NULL, E_PTHREAD), -1);
	while (j < table->nbr_philos)
	{
		if (pthread_join(table->philos[j].thread_id, NULL) != 0)
			return (error("JOIN", E_PTHREAD), -1);
		j++;
	}
	if (pthread_join(table->doctor, NULL) != 0)
		return (error("JOIN", E_PTHREAD), -1);
	return (0);
}

// ---------- //
// checks if nbr of meals is smaller or equal to 0
//  if so returns
// checks if there is only 1 philo
//  if so special case
// else creates philo threads
//  sets the starting time
// creates monitor thread
// waits to join all threads
// then joins monitor thread