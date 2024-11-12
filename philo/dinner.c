
#include "philo.h"

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

//-----------getters and setters-------//
// to avoid writing LOCK and UNLOCK
// --> ensures that the data is accessed in a safe environment (no data races)
// the functions have the pattern
//  mutex_lock
//  access/modify value
//  mutex_unlock




int dinner(t_table *table)
{

}