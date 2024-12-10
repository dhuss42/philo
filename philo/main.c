/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 12:07:19 by dhuss             #+#    #+#             */
/*   Updated: 2024/12/04 14:29:44 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_table	table;

	if (argc == 5 || argc == 6)
	{
		if (parser(&table, argv) == -1)
			return (-1);
		if (set_the_table(&table) == -1)
			return (-1);
		if (dinner(&table) == -1)
			return (-1);
		cleaner(&table);
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
