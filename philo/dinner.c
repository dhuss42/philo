/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 12:45:19 by dhuss             #+#    #+#             */
/*   Updated: 2024/11/21 12:56:58 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec + 1000 + tv.tv_usec / 1000);
}

//--desynchronise_philos--//
// if system contains even nbr of philos
//  if philo id is even
//      sleep for 30ms (half of minimum)
// if system is odd
//  if philos id is even
//      ->thinking

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

//---philo-died---//
// if get_bool philo hungry false (mutex)
//  return false
// if the time between last_meals of a philo is greater than time to die
//  set philo dead to true
//  lock the mutex (monitor/philo)

//---all_threads_running---//
// if threads = nbr of philos
//  return true
// wrap in mutex

bool	check_philo_died(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	pthread_mutex_lock(&table->philos->table->forks->fork);
	if (get_current_time() - philo->last_meal > table->time_to_die)
	{
		table->philo_died = true;
		printf("Philosopher has died.\n");
		pthread_mutex_unlock(&table->philos->table->forks->fork);
		return (true);
	}
	pthread_mutex_unlock(&table->philos->table->forks->fork);
	return (false);
}

void	*monitor_dinner(void *arg)
{
	t_table	*table;
	int	i;

	table = (t_table *)arg;
	while(!table->philo_died)
	{
		i = 0;
		while (i < table->nbr_philos)
		{
			if (check_philo_died(&table->philos[i]))
				return (NULL);
			i++;
		}
		usleep(1000); // not sure
	}
	return (NULL);
}

//-----monitor_dinner-----// (doctor)
// make sure all philos are running
// -> while (!all threads running)
// waits (;)
// while (!simulation_finished)
//  while (i < nbr_philo)
//      if (->philo_died)
//          ->set bool philo died
//          ->stauts philo died

//-----thinking-----//
//  -> status thinking
// if philo nbr is even
//  return ;

// time to think = time to eat * 2 - t_sleep // available time to think
// if t_think is negative
//      t_think = 0;
// -> custom ussleep(t_think * 42) (avoids double think by forcing philo to think and give opportunty for other philo to take the forkleaves 58% up to the system)

/* void	eat(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	pthread_mutex_lock(&philo->left_fork->fork);
	status_update(philo, "has taken left fork");
	pthread_mutex_lock(&philo->right_fork->fork);
	status_update(philo, "has taken right fork");

	stauts_update(philo, "is eating");
	philo->last_meal = get_current_time();
	philo->meals_eaten++;
	if (philo->meals_eaten = table->nbr_meals)
		// //  -> setter function philo hungry to false
	pthread_mutex_unlock(&philo->right_fork->fork);
	pthread_mutex_unlock(&philo->left_fork->fork);
} */

//------eat------//
// grab the forks left and right
//  Lock right and left fork
//  -> status took left and right fork
//
// eat: write eat, update last meal, update meals counter
//  hungry to true
// last meal time will also be read by the monitor thread and compared to time to die
// ----> needs a mutex (every philo has an internal mutex) add in .h file and in set_table
// -> setter function to that mutex 1:32
// increment meals eaten
// -> status eating
// -> custom usleep
// check if the amount of meals eaten is = nbr of meals
//  -> setter function philo hungry to false

// release the forks
//  UNLOCK both forks
//

//------status----------//
// add write_lock in h.
//  needs a safe write mutex
// get the elapsed time
//  gettime - start
// if the philosopher is not hungry
//  return
// lock wirte_mutex
    // if philo has taken right_fork or left_fork and the simulation has not finished
    //  print the elapsed time, philo id, has taken a fork
    // if philo is eating and simulation has not finished
    //  print the elapsed time, philo id, is eating
    // if philo is sleeping and simulation has not finished
    //  print the elapsed time, philo id, is sleeping
    // if philo is thinking and simulation has not finished
    //  print the elapsed time, philo id, is thinking
    // if philo has died
    //  print the elapsed time, philo id, died
// unlock write_mutex


//------custom usleep------//
// 1:20

void	wait_for_threads(t_table *table) // not correct
{
	int	i;

	i = 0;
	while(table->counter < table->nbr_philos)
	{
		pthread_join(table->philos[i].thread_id, NULL);
		i++;
	}
	// pthread_join(table->monitor, NULL);
}


/* int	spagethi_time(t_philo *philo)
{
	// desync philos

	while (!philo->table->philo_died)
	{
		// eat

	}
} */
//----------dinner simulation (spagethi time)----------//
//  wait for all threads --> extra function && bool in .h
//  synchronise start
//  set_long last_meal time(mutex);
//  counter that tracks the amount of threads (with mutex)
//  -> desynchronise philos
//
//  loop (as long as the simulation is not finished)
//      if a philo is not hungry break the loop
//      -> eat
//      -> sleep -> status & custom usleep
//      -> thinking

//----------dinner--------//
// if no meals (optional parameter)
//  return
// if only one philo
//  function

// create all threads, all philos
//  loop
//      pthread_create the function that is send with it is the dinner simulation

// add monitorthread in table struct
// Creat a monitor thread -> searches for dead philos
//  the function is monitor_dinner

//simulation start
// -> get the time
// -> set all threads ready bool to ture (add in table struct) -> by referenceing waiting for all threads
// synchronise the beginning
//    so that every philos starts together
//  loop through philos
//      Join threads
//  if we reach this line all philos are full
//  -> set_bool endsimulation to true (mutex)
// join the monitor

//-----------getters and setters-------//
// to avoid writing LOCK and UNLOCK
// --> ensures that the data is accessed in a safe environment (no data races)
// the functions have the pattern
//  mutex_lock
//  access/modify value
//  mutex_unlock


void	philo_simulation(t_table *table)
{
	printf("test waiting\n");
	while (!table->threads_ready)
	{
		usleep(100);
	}
	printf("philos are ready\n");
	while(!table->philo_died)
	{
		// spagethi_time(philo->table);
	}
}

int	dinner(t_table *table)
{
	int	i;

	i = 0;
	if (table->nbr_meals == 0)
		return (-1);
	if (table->nbr_philos == 1)
		// call single philo
	while (i < table->nbr_philos)
	{
		if (pthread_create(&table->philos->thread_id, NULL, &philo_simulation, NULL) != 0)
			return (-1);
		i++;
	}


	// if (pthread_create(&table->monitor, NULL, monitor_dinner, table) != 0)
	// 	return (-1);
	printf("TEST\n");
	table->threads_ready = true;
	wait_for_threads(table);
	return (0);

}
