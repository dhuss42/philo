/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_mutex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 10:56:58 by dhuss             #+#    #+#             */
/*   Updated: 2024/12/03 10:57:58 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	handle_mutex_lock(t_mtx *mutex, int router)
{
	if (router == LOCK)
	{
		if (pthread_mutex_lock(mutex) != 0)
			return (error("LOCK", E_MUTEX));
	}
	else if (router == UNLOCK)
	{
		if (pthread_mutex_unlock(mutex) != 0)
			return (error("UNLOCK", E_MUTEX));
	}
}
