
// #include "philo.h"


// bool    get_bool(t_mtx *mutex, bool *value)
// {
//     bool    ret;
//     pthread_mutex_lock(mutex);
//     ret = *value;
//     pthread_mutex_unlock(mutex);
//     return (ret);
// }

// void    wait_for_threads(t_table *table)
// {
//     while (!get_bool(&table->table_mutex, &table->threads_ready))
//         usleep(10);
// }

// void    *stuff(void *arg)
// {
//     t_philo *philo;

//     philo = (t_philo *)arg;
//     pthread_mutex_lock(&philo->table->table_mutex);
//     philo->table->ready_count++;
//     if (philo->table->ready_count == 5)
//     {
//         philo->table->threads_ready = true;
//     }
//     pthread_mutex_unlock(&philo->table->table_mutex);
//     wait_for_threads(philo->table);
//     printf("Philosopher %ld started.\n", (long)(philo - philo->table->philos));
//     return (NULL);
// }

// int main(void)
// {
//     t_table *table = NULL;
//     int i;
//     int j;

//     i = 0;
//     j = 0;
//     table = malloc(sizeof(t_table));
//     if (!table)
//         return (-1);
//     table->ready_count = 0;
//     table->threads_ready = false;
//     if (pthread_mutex_init(&table->table_mutex, NULL) != 0)
//         return (-1);
//     table->philos = malloc(sizeof(t_philo) * 5);
//     if (!table->philos)
//         return (-1);
//     while (i < 5)
//     {
//         table->philos[i].table = table;
//         if (pthread_create(&table->philos[i].thread_id, NULL, stuff, &table->philos[i]) != 0)
//         {
//             return (-1);
//         }
//         printf("created philo %d\n", i);
//         i++;
//     }
    
//     while (j < 5)
//     {
//         pthread_join(table->philos[j].thread_id, NULL);
//         j++;
//     }
//     printf("all threads joined\n");
//     free(table->philos);
//     free(table);
//     return (0);
// }
//     // allocate p_thread array
//     // create threads;
//     // make them wait till all are ready
//     // print message
//     // join threads