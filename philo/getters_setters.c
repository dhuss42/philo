/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_setters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 10:08:00 by dhuss             #+#    #+#             */
/*   Updated: 2024/11/25 10:08:04 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	set_bool(t_mtx *mutex, bool *dest, bool value)
{
	pthread_mutex_lock(mutex);
		// call error
	*dest = value;
	pthread_mutex_unlock(mutex);
		// call error
	return (0);
}

bool	get_bool(t_mtx *mutex, bool *value)
{
	bool	ret;

	pthread_mutex_lock(mutex);
	ret = *value;
	pthread_mutex_unlock(mutex);
	return (ret);
}

long   get_long(t_mtx *mutex, long *value)
{
	long	ret;

	pthread_mutex_lock(mutex);
	ret = *value;
	pthread_mutex_unlock(mutex);
	return (ret);
}

long	set_long(t_mtx *mutex, long *dest, long value)
{
	pthread_mutex_lock(mutex);
		// call error
	*dest = value;
	pthread_mutex_unlock(mutex);
		 // call error
	return (0);
}

