/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 10:08:35 by dhuss             #+#    #+#             */
/*   Updated: 2024/12/04 13:16:29 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	time_stamp(long start_time)
{
	struct timeval	ts;
	long			elapsed_ms;

	if (gettimeofday(&ts, NULL) == -1)
	{
		error(NULL, E_GETTIME);
	}
	elapsed_ms = ((ts.tv_sec) * 1000 + (ts.tv_usec) / 1000) - start_time;
	return (elapsed_ms);
}

int	set_start_time(t_table *table)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
	{
		return (error(NULL, E_GETTIME), -1);
	}
	table->start_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (0);
}

void	custom_usleep(long duration, t_table *table)
{
	struct timeval	start;
	struct timeval	now;
	long			start_time;
	long			elapsed_t;

	if (gettimeofday(&start, NULL) == -1)
	{
		return (error(NULL, E_GETTIME));
	}
	start_time = (start.tv_sec * 1000) + (start.tv_usec / 1000);
	while (1)
	{
		if (gettimeofday(&now, NULL) == -1)
		{
			return (error(NULL, E_GETTIME));
		}
		elapsed_t = ((now.tv_sec * 1000) + (now.tv_usec / 1000)) - start_time;
		if (elapsed_t >= duration)
			break ;
		if (get_bool(&table->table_mutex, &table->finished) == true)
			return ;
		usleep(100);
	}
}
