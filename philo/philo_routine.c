
#include "philo.h"

void    write_status(t_philo *philo, const char *status)
{
    long elapsed_time;

    // printf(YELLOW"locking philo mutex\n"WHITE);
    pthread_mutex_lock(&philo->philo_mutex);
    if (philo->full || get_bool(&philo->table->table_mutex, &philo->table->philo_died))
    {
        printf(RED"Philsopher %d is full or has died\n"WHITE, philo->id);
        pthread_mutex_unlock(&philo->philo_mutex);
        return ;
    }
    pthread_mutex_unlock(&philo->philo_mutex);
    elapsed_time = time_stamp(philo->table->start_time);
    // printf(GREEN"unlock philo mutex\n"WHITE);

    // printf(YELLOW"locking write mutex\n"WHITE);
    pthread_mutex_lock(&philo->table->write_mutex);
    printf("[%ld ms] Philosopher %d %s\n", elapsed_time, philo->id, status);
    pthread_mutex_unlock(&philo->table->write_mutex);
    // printf(GREEN"unlocking write mutex\n"WHITE);
}

//-------------------------//
// checks if the philo is full or if a philo died
//      prints according message
//          ----> not sure if the message should be printed here
// gets time passed since start
// prints status message that was passed as arg


void    eat(t_philo *philo)
{
    if (philo->id % 2 == 0)
    {
        pthread_mutex_lock(&philo->left_fork->fork);
        // write_status(philo, "has taken the left fork");
        pthread_mutex_lock(&philo->right_fork->fork);
        // write_status(philo, "has taken the right fork");
    }
    else
    {
        pthread_mutex_lock(&philo->right_fork->fork);
        // write_status(philo, "has taken the right fork");
        pthread_mutex_lock(&philo->left_fork->fork);
        // write_status(philo, "has taken the left fork");
    }
    pthread_mutex_lock(&philo->philo_mutex);
    philo->last_meal = time_stamp(philo->table->start_time);
    philo->meals_eaten++;
    pthread_mutex_unlock(&philo->philo_mutex);
    write_status(philo, "is eating");
    pthread_mutex_unlock(&philo->right_fork->fork);
    usleep(philo->table->time_to_eat);
    pthread_mutex_unlock(&philo->left_fork->fork);
    if (philo->meals_eaten == philo->table->nbr_meals)
    {
        set_bool(&philo->philo_mutex, &philo->full, true);
    }
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


void    custom_sleep(t_philo *philo)
{
    t_table *table;

    table = philo->table;
    write_status(philo, "is sleeping");
    // long start_sleep = time_stamp(table->start_time);
    usleep(table->time_to_sleep);
    // long end_sleep = time_stamp(table->start_time);
    // printf("Philosoper %d slept for %ld ms\n", philo->id, end_sleep - start_sleep);
}

// wirtes status sleeping
// sleeps for time_to_sleep

//------custom usleep------//
// 1:20

void    think(t_philo *philo)
{
    t_table *table;
    long    think_time;

    table = philo->table;
    write_status(philo, "is thinking");
    if (table->nbr_philos % 2 == 0)
        return ;
    think_time = (table->time_to_eat * 2) - table->time_to_sleep;
    if (think_time < 0)
        think_time = 0;
    usleep(think_time);
    // printf("Philosopher %d thought for %ld ms\n", philo->id, think_time);
}

// writes status is thinking
// if philo_nbr is even the function returns
// ---> an even numbered simulation is in itself fait
// if not even has to think long
// ---> need to look up why this length

