/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyavroya <tyavroya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:37:42 by tyavroya          #+#    #+#             */
/*   Updated: 2024/07/08 17:31:13 by tyavroya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void *_safe_malloc(size_t bytes)
{
	void	*ret;

	ret = malloc(bytes);
	if (!ret)
		_err("Bad malloc");
	return (ret);
}

static void	handle_thread_error(int status, t_opcode code)
{
	if (EAGAIN == status)
		_err("No resources to create another thread");
	else if (EPERM == status)
		_err("The caller does not have appropriate permission\n");
	else if (EINVAL == status && CREATE == code)
		_err("The value specified by attr is invalid.");
	else if (EINVAL == status && (JOIN == code || DETACH == code))
		_err("The value specified by thread is not joinable\n");
	else if (ESRCH == status)
		_err("No thread could be found corresponding to that specified by"
				"the given threa d ID, thread.");
	else if (EDEADLK == status)
		_err("A deadlock was detected or the value of thread specifies"
				"the calling thread.");
}

void	safe_thread_handle(pthread_t *thread, t_fptr foo, void *data,
		t_opcode code)
{
	if (CREATE == code)
		handle_thread_error(pthread_create(thread, NULL, foo, data), code);
	else if (JOIN == code)
		handle_thread_error(pthread_join(*thread, NULL), code);
	else if (DETACH == code)
		handle_thread_error(pthread_detach(*thread), code);
	else
		_err("Wrong code for thread_handle: use <CREATE> <JOIN> <DETACH>");
}

static void	handle_mutex_error(int status, t_opcode code)
{
	if (EINVAL == status && (LOCK == code || UNLOCK == code))
		_err("The value specified by mutex is invalid");
	else if (EINVAL == status && INIT == code)
		_err("The value specified by attr is invalid.");
	else if (EDEADLK == status)
		_err("A deadlock could occur if the thread "
				"blocked waiting for mutex.");
	else if (EPERM == status)
		_err("The current thread does not hold a lock on mutex.");
	else if (ENOMEM == status)
		_err("The process cannot allocate enough memory to create another mutex.");
	else if (EBUSY == status)
		_err("Mutex is locked");
}

void	_safe_mutex_handle(t_mutex *mtx, t_opcode opcode)
{
	if (opcode == LOCK)
		handle_mutex_error(pthread_mutex_lock(mtx), opcode);
	else if (opcode == UNLOCK)
		handle_mutex_error(pthread_mutex_unlock(mtx), opcode);
	else if (opcode == INIT)
		handle_mutex_error(pthread_mutex_init(mtx, NULL), opcode);
	else if (opcode == DESTROY)
		handle_mutex_error(pthread_mutex_destroy(mtx), opcode);
	else
		_err("Wrong opcode for mutex handle");
}