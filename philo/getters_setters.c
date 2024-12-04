/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_setters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 10:08:00 by dhuss             #+#    #+#             */
/*   Updated: 2024/12/03 15:16:47 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	set_bool(t_mtx *mutex, bool *dest, bool value)
{
	if (pthread_mutex_lock(mutex) != 0)
		return (error("set_bool LOCK", E_MUTEX), -1);
	*dest = value;
	if (pthread_mutex_unlock(mutex) != 0)
		return (error("set_bool UNLOCK", E_MUTEX), -1);
	return (0);
}

bool	get_bool(t_mtx *mutex, bool *value)
{
	bool	ret;

	if (pthread_mutex_lock(mutex) != 0)
		error("get_bool LOCK", E_MUTEX);
	ret = *value;
	if (pthread_mutex_unlock(mutex) != 0)
		error("get_bool UNLOCK", E_MUTEX);
	return (ret);
}

long	get_long(t_mtx *mutex, long *value)
{
	long	ret;

	if (pthread_mutex_lock(mutex) != 0)
		return (error("get_long LOCK", E_MUTEX), -1);
	ret = *value;
	if (pthread_mutex_unlock(mutex) != 0)
		return (error("get_long UNLOCK", E_MUTEX), -1);
	return (ret);
}

long	set_long(t_mtx *mutex, long *dest, long value)
{
	if (pthread_mutex_lock(mutex) != 0)
		return (error("set_long LOCK", E_MUTEX), -1);
	*dest = value;
	if (pthread_mutex_unlock(mutex) != 0)
		return (error("set_long UNLOCK", E_MUTEX), -1);
	return (0);
}

void	increment_int(t_mtx *mutex, int *counter)
{
	handle_mutex_lock(mutex, LOCK);
	((*counter)++);
	handle_mutex_lock(mutex, UNLOCK);
}
