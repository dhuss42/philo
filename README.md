# philo
This project was about learning the basics of threading a process. To be more specific it was about creating threads and implementing mutexes.

## Contents

1. [Project overview](#1-Project-overview)
2. [Project structure](#2-Project-structure)
3. [Description of individual steps](#3-Description-of-individual-steps)

## 1. Project overview

## 2. Project structure

1.  [Parser](#31-Parser)
2.  [Setting the table](#32-Setting-the-table)
3.  [Loop](#33-Loop)
4.  [Cleaning up](##34-Cleaning-up)

## 3. Description of individual steps

The following is a description of the logical steps of the philo program

### 3.1 Parser

The parser function validates and converts input arguments into appropriate long integer values for the table structure. It begins by checking if the input strings represent valid numeric values (excluding alphabetic characters and invalid symbols). The ft_atol function converts these strings to long integers, ensuring they are within a valid range and not exceeding INT_MAX. The parser also checks if the converted values are above certain minimum limits (e.g., 60 milliseconds) for specific parameters like time_to_die, time_to_eat, and time_to_sleep. If any error is detected during these checks, it returns -1; otherwise, it populates the t_table structure with the parsed values.

### 3.2 Setting the table

### 3.3 Loop

### 3.4 Cleaning up

## 4. Run it

Copy the following code to run philo 

```
git clone 
cd philo/philo
make
./philo 7 250 250 250 5
```
