/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 10:08:35 by dhuss             #+#    #+#             */
/*   Updated: 2024/11/25 11:45:59 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long time_stamp(long	start_time)
{
	struct timeval ts;
	long	elapsed_ms;

	if (gettimeofday(&ts, NULL) == -1)
	{
		// call error
	}
	elapsed_ms = ((ts.tv_sec) * 1000 + (ts.tv_usec) / 1000) - start_time;
	return (elapsed_ms);
}

void	set_start_time(t_table *table)
{
	struct timeval tv;

	if (gettimeofday(&tv, NULL) == -1)
	{
		// call error
	}
	table->start_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	// printf("start_time %ld\n", table->start_time);
}
//--------//
// gets time of day
// sets start time in ms in table struct
// later time_stamp function will take the start_time
// and subtract the current time to get the elapsed time

void	custom_usleep(long duration)
{
	struct timeval start;
	struct timeval now;

	long start_time;
	long elapsed_time;

	if (gettimeofday(&start, NULL) == -1)
	{
		// error
		return ;
	}
	start_time = (start.tv_sec * 1000) + (start.tv_usec / 1000);
	while (1)
	{
		if (gettimeofday(&now, NULL) == -1)
		{
			// error
			return ;
		}
		elapsed_time = ((now.tv_sec * 1000) + (now.tv_usec / 1000)) - start_time;
		if (elapsed_time >= duration)
			break ;
		usleep(100);
	}
}

// getting current time of the day
// converting current time of day into ms
// loop
//	get current time again
//	calc elapsed time by subtracting the two
//	if the elapsed time is = or bigger than the passed duration break the loop
//	sleep for short periods to reduce cpu usage