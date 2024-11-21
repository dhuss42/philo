/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 12:07:19 by dhuss             #+#    #+#             */
/*   Updated: 2024/11/21 12:45:30 by dhuss            ###   ########.fr       */
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

		//  clean if 1 philo dies or everyone is full
	}
	else
		error_handling(NULL, "wrong number of arguments");
	return (0);
}

// might have to implement return statements to the main function as exit is not allowed
