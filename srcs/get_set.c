/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyavroya <tyavroya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 18:50:14 by tyavroya          #+#    #+#             */
/*   Updated: 2024/08/31 16:07:24 by tyavroya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

bool	get_bool(t_mutex *mutex, bool *val)
{
	bool	res;

	safe_mutex_handle(mutex, LOCK);
	res = *val;
	safe_mutex_handle(mutex, UNLOCK);
	return (res);
}

void	set_bool(t_mutex *mutex, bool *dest, bool val)
{
	safe_mutex_handle(mutex, LOCK);
	*dest = val;
	safe_mutex_handle(mutex, UNLOCK);
}

long	get_long(t_mutex *mutex, long *val)
{
	long	res;

	safe_mutex_handle(mutex, LOCK);
	res = *val;
	safe_mutex_handle(mutex, UNLOCK);
	return (res);
}

void	set_long(t_mutex *mutex, long *dest, long val)
{
	safe_mutex_handle(mutex, LOCK);
	*dest = val;
	safe_mutex_handle(mutex, UNLOCK);
}

bool	simulation_finished(t_table *table)
{
	return (get_bool(&table->table_mutex, &table->end_simulation));
}
