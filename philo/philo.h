
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
#define RESET       "\033[0m"
#define BLACK       "\033[30m"
#define RED         "\033[31m"
#define GREEN       "\033[32m"
#define YELLOW      "\033[33m"
#define BLUE        "\033[34m"
#define MAGENTA     "\033[35m"
#define CYAN        "\033[36m"
#define WHITE       "\033[37m"

// struct that holds the info

typedef pthread_mutex_t t_mtx;

typedef struct s_table t_table;

typedef struct s_fork
{
    t_mtx   fork;
    int     fork_id;
} t_fork;

typedef struct s_philo
{
    int     id;
    long    meals_eaten; // for optional variable
    bool    hungry;
    long    last_meal; // time passed from last meal
    t_fork  *left_fork;
    t_fork  *right_fork;
    pthread_t   thread_id;
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
    t_fork  *forks;
    t_philo *philos;
};

int     parser(t_table *table, char **argv);
int    set_the_table(t_table *table);

void    error_handling(char *str, char *error_msg);

#endif