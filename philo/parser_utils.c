/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:38:20 by dhuss             #+#    #+#             */
/*   Updated: 2024/12/04 14:41:03 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	ft_isspace(char c)
{
	if ((c >= 9 && c <= 12) || c == 32)
		return (true);
	return (false);
}

int	not_a_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!((str[i] >= '0' && str[i] <= '9') || str[i] == '+'
				|| str[i] == '-' || ft_isspace(str[i])))
			return (-1);
		i++;
	}
	return (0);
}
