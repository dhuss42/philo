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
	if (pthread_mutex_lock(mutex) != 0)
		return (error(NULL, E_MUTEX), -1);
	*dest = value;
	pthread_mutex_unlock(mutex);
		return (error(NULL, E_MUTEX), -1);
	return (0);
}

bool	get_bool(t_mtx *mutex, bool *value)
{
	bool	ret;

	if (pthread_mutex_lock(mutex) != 0)
		error(NULL, E_MUTEX);
	ret = *value;
	if (pthread_mutex_unlock(mutex) != 0)
		error(NULL, E_MUTEX);
	return (ret);
}

long   get_long(t_mtx *mutex, long *value)
{
	long	ret;

	if (pthread_mutex_lock(mutex) != 0)
		return (error(NULL, E_MUTEX), -1);
	ret = *value;
	if (pthread_mutex_unlock(mutex) != 0)
		return (error(NULL, E_MUTEX), -1);
	return (ret);
}

long	set_long(t_mtx *mutex, long *dest, long value)
{
	if (pthread_mutex_lock(mutex) != 0)
		return (error(NULL, E_MUTEX), -1);
	*dest = value;
	pthread_mutex_unlock(mutex);
		return (error(NULL, E_MUTEX), -1);
	return (0);
}
