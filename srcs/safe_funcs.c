/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyavroya <tyavroya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:37:42 by tyavroya          #+#    #+#             */
/*   Updated: 2024/09/14 18:37:24 by tyavroya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static bool	handle_thread_error(int status, t_opcode code)
{
	if (EAGAIN == status)
		return (false);
	else if (EPERM == status)
		return (false);
	else if (EINVAL == status && CREATE == code)
		return (false);
	else if (EINVAL == status && (JOIN == code || DETACH == code))
		return (false);
	else if (ESRCH == status)
		return (false);
	else if (EDEADLK == status)
		return (false);
	return (true);
}

bool	safe_thread_handle(pthread_t *thread, t_fptr foo, void *data,
		t_opcode code)
{
	if (CREATE == code)
		return (handle_thread_error(pthread_create(thread, NULL, foo, data),
				code));
	else if (JOIN == code)
		return (handle_thread_error(pthread_join(*thread, NULL), code));
	else if (DETACH == code)
		return (handle_thread_error(pthread_detach(*thread), code));
	else
		return (false);
}

static bool	handle_mutex_error(int status, t_opcode code)
{
	if (EINVAL == status && (LOCK == code || UNLOCK == code))
		return (false);
	else if (EINVAL == status && INIT == code)
		return (false);
	else if (EDEADLK == status)
		return (false);
	else if (EPERM == status)
		return (false);
	else if (ENOMEM == status)
		return (false);
	else if (EBUSY == status)
		return (false);
	return (true);
}

bool	safe_mutex_handle(t_mutex *mtx, t_opcode opcode)
{
	if (opcode == LOCK)
		return (handle_mutex_error(pthread_mutex_lock(mtx), opcode));
	else if (opcode == UNLOCK)
		return (handle_mutex_error(pthread_mutex_unlock(mtx), opcode));
	else if (opcode == INIT)
		return (handle_mutex_error(pthread_mutex_init(mtx, NULL), opcode));
	else if (opcode == DESTROY)
		return (handle_mutex_error(pthread_mutex_destroy(mtx), opcode));
	else
		return (false);
}
