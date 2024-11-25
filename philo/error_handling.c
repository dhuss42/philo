/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 12:07:24 by dhuss             #+#    #+#             */
/*   Updated: 2024/11/14 12:07:25 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

void	error_handling(char *str, char *error_msg)
{
	printf("Error: ");
	if (str)
		printf("%s: ", str);
	printf("%s\n", error_msg);
}
