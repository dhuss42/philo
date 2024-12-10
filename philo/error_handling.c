/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 12:07:24 by dhuss             #+#    #+#             */
/*   Updated: 2024/12/03 15:17:35 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// could change this to set a bool to true
// something like end simulation
// monitor checks if end simulation is true
// exits if an error occureds

void	ft_putchar(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		write (2, &str[i++], 1);
	write (2, ": ", 2);
}

void	error(char *str, t_error error_code)
{
	int		i;
	char	*msg;

	i = 0;
	if (error_code == E_ARGS)
		msg = "Error: wrong number of arguments\n";
	if (error_code == E_INVALIDINPT)
		msg = "Error: invalid input\n";
	if (error_code == E_ALLOC)
		msg = "Error: allocation\n";
	if (error_code == E_MUTEX)
		msg = "Error: mutex\n";
	if (error_code == E_PTHREAD)
		msg = "Error: pthread\n";
	if (error_code == E_GETTIME)
		msg = "Error: gettimeofday\n";
	if (str)
		ft_putchar(str);
	while (msg[i] != '\0')
		write (2, &msg[i++], 1);
}
