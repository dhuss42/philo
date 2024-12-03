/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 12:07:19 by dhuss             #+#    #+#             */
/*   Updated: 2024/11/25 10:10:25 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_table table;

    if (argc == 5 || argc == 6)
    {
        if (parser(&table, argv) == -1)
            return (-1);
        if (set_the_table(&table) == -1)
            return (-1);
        if (dinner(&table) == -1)
            return (-1);
        //  looping
        cleaner(&table);
        //  clean if 1 philo dies or everyone is full
    }
    else
        error(NULL, E_ARGS);
    return (0);
}

// [nbr_philo]
// [time_to_die]
// [time_to_eat]
// [time_to_sleep]
// [nbr_meals]

// 5 800 200 200
// --> passes (no philo should die)
// 5 800 200 200 7
// --> not all philos eat seven times
// 4 410 200 200
// --> passes (no philos should die)

