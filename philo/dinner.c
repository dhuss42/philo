
#include "philo.h"

long    get_current_time_ms()
{
    struct timeval tv;
    long    time_ms;

    time_ms = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
    gettimeofday(&tv, NULL);
    printf("Current TIme: %ld ms\n", time_ms);
    return (time_ms);

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

void    write_status(t_philo *philo, const char *status)
{
    long elapsed_time;

    pthread_mutex_lock(&philo->philo_mutex);
    if (philo->full || get_bool(&philo->table->table_mutex, &philo->table->philo_died))
    {
        pthread_mutex_unlock(&philo->philo_mutex);
        return ;
    }
    pthread_mutex_unlock(&philo->philo_mutex);
    elapsed_time = get_current_time_ms() - philo->table->start_time;
    pthread_mutex_lock(&philo->table->write_mutex);
    printf("[%ld ms] Philosopher %d %s\n", elapsed_time, philo->id, status);
    pthread_mutex_unlock(&philo->table->write_mutex);
}

void    eat(t_philo *philo)
{
    // t_table *table;

    // table = philo->table;
    // printf("TEST\n");
    // printf("id: %d\n", philo->id);
    if (philo->id % 2 == 0)
    {
        pthread_mutex_lock(&philo->left_fork->fork);
        write_status(philo, "has taken the left fork");
        pthread_mutex_lock(&philo->right_fork->fork);
        write_status(philo, "has taken the right fork");
    }
    else
    {
        pthread_mutex_lock(&philo->right_fork->fork);
        write_status(philo, "has taken the right fork");
        pthread_mutex_lock(&philo->left_fork->fork);
        write_status(philo, "has taken the left fork");
    }
    pthread_mutex_lock(&philo->philo_mutex);
    philo->last_meal = get_current_time_ms();
    philo->meals_eaten++;
    pthread_mutex_unlock(&philo->philo_mutex);
    write_status(philo, "is eating");
    pthread_mutex_unlock(&philo->right_fork->fork);
    pthread_mutex_unlock(&philo->left_fork->fork);
    if (philo->meals_eaten == philo->table->nbr_meals)
    {
        set_bool(&philo->philo_mutex, &philo->full, true);
    }
}

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
// if the philosopher is full
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

//-------waiting for all threads-------//
//  loop ( while all the threads are not ready)
//     ;

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

void    wait_threads(t_table *table)
{
    while (!get_bool(&table->table_mutex, &table->threads_ready))
        usleep(10);
}

void    *health_check(void *arg)
{
    t_table *table;
    long    current_time;
    int i;

    table = (t_table *)arg;
    i = 0;
    while (1)
    {
        pthread_mutex_lock(&table->table_mutex);
        while (i < table->nbr_philos)
        {
            current_time = get_current_time_ms();
            printf("current_time %lu\n", current_time);
            printf("TEST\n");
            // if (current_time - table->philos[i].last_meal > table->time_to_die)
            // {
            //     printf("Philosopher %d has died!\n", i);
            //     table->philo_died = true;
            //     pthread_mutex_unlock(&table->table_mutex);
            //     return (NULL);
            // }
            printf("TEST2\n");
            i++;
        }
        pthread_mutex_unlock(&table->table_mutex);
        usleep(1000 * 10); // random
    }
    return (NULL);
}

void *spagethi_time(void *arg) // why void pointer?
{
    t_philo *philo;

    philo = (t_philo *)arg;
    pthread_mutex_lock(&philo->table->table_mutex);
    philo->table->ready_count++;
    if (philo->table->ready_count == philo->table->nbr_philos)
    {
        philo->table->threads_ready = true;
    }
    pthread_mutex_unlock(&philo->table->table_mutex);
    wait_threads(philo->table);
    printf("Philosopher %d started at elapsed time: %ld ms\n", philo->id, get_current_time_ms() - philo->table->start_time);
    // printf("threads ready\n");
    while (!philo->table->philo_died)
    {
        if (philo->full)
            break ;
        eat(philo);
    }
    return (NULL);
}

int dinner(t_table *table)
{
    int i;

    i = 0;
    exit(EXIT_SUCCESS);
    if (table->nbr_meals <= 0)
        return (-1);
    // else if (table->nbr_philos == 1)
    //     // single philo function
    else
    {
        while (i < table->nbr_philos)
        {
            table->philos[i].table = table;
            if (pthread_create(&table->philos[i].thread_id, NULL, spagethi_time, &table->philos[i]) != 0)
            {
                return (-1);
            }
            printf("created philo %d\n", i);
            i++;
        }
    }
    table->start_time = get_current_time_ms();
    // pthread_create(&table->doctor, NULL, health_check, &table);
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

// to do 
// get philos created and waiting until everyone is ready
