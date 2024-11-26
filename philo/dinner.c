/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 12:45:19 by dhuss             #+#    #+#             */
/*   Updated: 2024/11/25 14:10:18 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//--single-philo---//
// 1 fake to lock the fork
// 2 sleep until monitor will bust it
// -> wait for all threads
// -> set_long last meal time (mutex)
// -> increase nbr of threads that are running
// -> write status taking fork
// while (!simulation_finished)
//  usleep(200)
// return (NULL)

void    wait_threads(t_table *table)
{
    while (!get_bool(&table->table_mutex, &table->threads_ready))
        usleep(10);
}

void    desync(t_philo *philo)
{
    t_table *table;

    table = philo->table;
    if (table->nbr_philos % 2 == 0)
    {
        if (philo->id % 2 == 0)
            usleep(30000); //
    }
    else
    {
        if (philo->id % 2 == 0)
            think(philo);
    }
}

//------------//
// checks if the total amount of philos is even
//    if so it checks whether the current philo has an even position
//      if so it sleeps
// if the total amount of philos is uneven
//     the even numbered philos think first
//---> to make the simulation fair

void *spagethi_time(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    pthread_mutex_lock(&philo->table->table_mutex);
	// printf("philo: adress table %p\n", philo->table);
    philo->table->ready_count++;
    // printf(GREEN"ready_count: %d\n"WHITE, philo->table->ready_count);
    if (philo->table->ready_count == philo->table->nbr_philos)
    {
        philo->table->threads_ready = true;
    }
    pthread_mutex_unlock(&philo->table->table_mutex);
    wait_threads(philo->table);
    // set last_meal_time ??
    // desync(philo);

    // printf("Philosopher %d started at elapsed time: %ld ms\n", philo->id, time_stamp(philo->table->start_time));
    // printf("threads ready\n");
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
        // exit(EXIT_SUCCESS);
}

//---------//
// philo threads run through this function
// threads wait until all threads are ready
//      lock mutex, add to counter,
//      if counter = nbr of philos -> threads_ready true
//      unlock mutex
//      calls threads wait until threads_ready is set to true
// calls desync threads
//
// loop through routine until a philo is dead
//      if a philo has eaten nbr_meals times break;
//      calls eat
//      calls sleep
//      calls think


int dinner(t_table *table)
{
    int i;

    i = 0;
    if (table->nbr_meals <= 0)
        return (-1);
    else if (table->nbr_philos == 1)
    {
        if (pthread_create(&table->philos[0].thread_id, NULL, single_philo, &table->philos[0]) != 0)
            return (-1);
    }
    else
    {
        while (i < table->nbr_philos)
        {
            table->philos[i].table = table;
            if (pthread_create(&table->philos[i].thread_id, NULL, spagethi_time, &table->philos[i]) != 0)
                return (-1);
            i++;
        }
    }
    handle_mutex_lock(&table->table_mutex, LOCK);
    set_start_time(table);
    handle_mutex_lock(&table->table_mutex, UNLOCK);
    if (pthread_create(&table->doctor, NULL, monitor_dinner, table) != 0)
		return (-1);
    int j = 0;
    while (j < table->nbr_philos)
    {
        pthread_join(table->philos[j].thread_id, NULL);
        j++;
    }
    pthread_join(table->doctor, NULL);

    printf("Simulation ended\n");
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