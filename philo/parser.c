/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 12:07:08 by dhuss             #+#    #+#             */
/*   Updated: 2024/12/04 14:40:44 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atol(char *str)
{
	int		i;
	int		sign;
	long	result;

	i = 0;
	sign = 1;
	result = 0;
	if (not_a_digit(str) == -1)
		return (-1);
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			return (-1);
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
		if (result > INT_MAX)
			return (-1);
	}
	return (result * sign);
}

// skips whitespaces
// checks for negative values
// converts to long and checks for INT_MAX

int	parser(t_table *table, char **argv)
{
	table->nbr_philos = ft_atol(argv[1]);
	if (table->nbr_philos <= 0)
		return (error("nbr_philos", E_INVALIDINPT), -1);
	table->time_to_die = ft_atol(argv[2]);
	if (table->time_to_die == -1)
		return (error("time_to_die", E_INVALIDINPT), -1);
	table->time_to_eat = ft_atol(argv[3]);
	if (table->time_to_eat == -1)
		return (error("time_to_eat", E_INVALIDINPT), -1);
	table->time_to_sleep = ft_atol(argv[4]);
	if (table->time_to_sleep == -1)
		return (error("time_to_sleep", E_INVALIDINPT), -1);
	if (argv[5])
	{
		table->nbr_meals = ft_atol(argv[5]);
		if (table->nbr_meals <= 0)
			return (error("nbr_meals", E_INVALIDINPT), -1);
	}
	return (0);
}
