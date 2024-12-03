/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 12:06:35 by dhuss             #+#    #+#             */
/*   Updated: 2024/11/25 11:10:12 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/time.h>
#include <sys/_types.h>
#include <string.h>
#include <pthread.h>
#include <limits.h>

//----------------colors--------------//
#define RESET	   "\033[0m"
#define BLACK	   "\033[30m"
#define RED		 "\033[31m"
#define GREEN	   "\033[32m"
#define YELLOW	  "\033[33m"
#define BLUE		"\033[34m"
#define MAGENTA	 "\033[35m"
#define CYAN		"\033[36m"
#define WHITE	   "\033[37m"

// struct that holds the info

typedef pthread_mutex_t t_mtx;

typedef struct s_table t_table;

typedef struct s_fork
{
	t_mtx   fork;
	int	 fork_id;
} t_fork;

typedef struct s_philo
{
    int     id;
    long    meals_eaten; // for optional variable
    bool    full;
    bool    dead;
    long    last_meal; // time passed from last meal
    t_fork  *left_fork;
    t_fork  *right_fork;
    pthread_t   thread_id;
    t_mtx   philo_mutex;
    t_table *table;
} t_philo;

struct s_table
{
    long    nbr_philos;
    long    time_to_die;
    long    time_to_eat;
    long    time_to_sleep;
    long    nbr_meals;
    long    start_time;
    bool    philo_died;
    bool    finished;
    bool    threads_ready;
    int     ready_count;
    t_mtx   table_mutex;
    t_mtx   write_mutex;
    t_fork  *forks;
    t_philo *philos;
    pthread_t   doctor;
};

typedef enum e_router
{
    LOCK,
    UNLOCK,
}   t_router;

typedef enum e_error
{
    E_ARGS,
    E_INVALIDINPT,
    E_UNDERMINMS,
    E_PTHREAD,
    E_MUTEX,
    E_ALLOC,
    E_GETTIME,
} t_error;

int     parser(t_table *table, char **argv);
int     set_the_table(t_table *table);
int     dinner(t_table *table);

void    *single_philo(void *arg);
void    *monitor_dinner(void *arg);
void    wait_threads(t_table *table);

void    set_start_time(t_table *table);
long    time_stamp(long    start_time);
void	custom_usleep(long duration, t_table *table);

void    think(t_philo *philo);
void    custom_sleep(t_philo *philo);
void    eat(t_philo *philo);
void    write_status(t_philo *philo, const char *status);

int     set_bool(t_mtx *mutex, bool *dest, bool value);
bool    get_bool(t_mtx *mutex, bool *value);
long    get_long(t_mtx *mutex, long *value);
long    set_long(t_mtx *mutex, long *dest, long value);
void    handle_mutex_lock(t_mtx *mutex, int router);
void    cleaner(t_table *table);
void	error(char *str, t_error error_code);

#endif