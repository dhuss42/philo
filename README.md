# Philosophers

## Contents

1. [Project overview](#1-Project-overview)
2. [Project structure](#2-Project-structure)
3. [Description of individual steps](#3-Description-of-individual-steps)
4. [Run it](#4-Run-it)

## 1. Project overview
This project was about learning the basics of threading a process. To be more specific it was about creating threads and implementing mutexes.

## 2. Project structure

1.  [Parser](#31-Parser)
2.  [Setting the table](#32-Setting-the-table)
3.  [Simulation](#33-Simulation)
4.  [Cleaning up](##34-Cleaning-up)

## 3. Description of individual steps

The following is a description of the logical steps of the philo program. It takes the arguments: number of philos; time to die; time to eat; time to sleep; and optionally number of meals.

### 3.1 Parser

The parser validates and converts input arguments into appropriate long integer values for the table structure. It begins by checking if the input strings represent valid numeric values (excluding alphabetic characters and invalid symbols). The ft_atol function converts these strings to long integers, ensuring they are within a valid range and not exceeding INT_MAX. If any error is detected during these checks, it returns an error; otherwise, it populates the t_table structure with the parsed values.

### 3.2 Setting the table

The set_the_table function is responsible for setting up the philosophers' dining environment by allocating and initializing the necessary data structures. First, it allocates memory for the philosophers and forks arrays. Each fork is associated with a mutex (pthread_mutex_t), which is initialized to ensure that only one philosopher can hold a fork at any given time, preventing concurrent access issues. The set_philo function then initializes each philosopher's properties, such as their unique ID, hunger status, and meal counter, and assigns them their respective forks. For even-numbered philosophers, the fork assignment is reversed to reduce the risk of deadlock, allowing for a circular fork arrangement.

### 3.3 Simulation

Each philosopher is represented by a separate thread. Philosophers alternately think, eat, and sleep, with the requirement that they must use shared resources (forks) to eat.

After creation all philosopher threads, they wait until every thread is ready to ensure a simultaneous start. To prevent potential deadlocks or unfair access to forks, even-numbered philosophers are desynchronized to begin with the "thinking" phase.

Each philosopher thread runs a loop until the simulation ends. During each iteration, the thread checks if the philosopher is "full" (has eaten the required number of meals) or "dead" (due to exceeding the time limit without eating).

The philosopher then performs the following actions:

*Eating*
The philosopher attempts to acquire two forks (mutex-protected), blocking access to them for other threads.
A status message is logged, including the timestamp (in milliseconds), the philosopher’s number, and a message indicating the fork has been taken.
The last meal time for the philosopher is updated, and a status message indicates that the philosopher is eating.
The thread then waits for a specified duration to simulate eating, and a counter tracking how many times the philosopher has eaten is incremented.
If the philosopher has eaten the required number of meals, a flag is set to indicate they are "full."

*Sleeping*
After eating, the philosopher logs a status message and enters the sleeping phase for a specified duration.

*Thinking*
After sleeping, the philosopher logs another status message and begins thinking.
For even-numbered philosophers, the system is inherently fair, so no special action is taken. However, if the number oh philosophers is not even, the thinking time hast to be adjusted to make the system fair in every situation (sometimes philos will eat twice in a row because they blocked the forks twice in a row). The possible time to think is time to eat * 2 - time to sleep. In order to avoid a philo eating twice in a row the philo will forcefully think for at least 50% of the possible time to tink.

Monitor thread
A separate monitor thread oversees the simulation, ensuring its termination under specific conditions. If any philosopher has "died" (exceeded their allowed time without eating), or
if all philosophers are "full" (have completed the required number of meals) the monitor sets a flag to signal the simulation’s completion.
    
To ensure thread safety and prevent race conditions, various mutexes are employed

    Philosopher Mutexes: Protect access to variables within each philosopher's data structure.
    Table Mutexes: Protect shared variables in the table structure, such as flags or global states.
    Fork Mutexes: Control access to the shared forks, ensuring only one philosopher can hold a fork at any given time.
    Write Mutexes: Ensure thread-safe logging of status messages.

Once the simulation concludes, all threads (philosophers and the monitor) are joined together.

### 3.4 Cleaning up

At the conclusion of the simulation, the program performs cleanup to release allocated resources and ensure proper shutdown. All the mutexes are destroyed and the forks and philo arrays are freed.

## 4. Run it

Copy the following code to run philo 

```
git clone 
cd philo/philo
make
./philo 5 610 200 200 5
```
