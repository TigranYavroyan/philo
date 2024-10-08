/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigran <tigran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 19:07:27 by tyavroya          #+#    #+#             */
/*   Updated: 2024/09/11 00:11:24 by tigran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

long	gettime(t_time_code time_code)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	if (time_code == MILLISECONDS)
		return ((tv.tv_usec / 1e3) + (tv.tv_sec * 1e3));
	if (time_code == MICROSECONDS)
		return (tv.tv_usec + (tv.tv_sec * 1e6));
	return (42);
}

void	ft_usleep(long usec, t_table *table)
{
	long	start;

	start = gettime(MICROSECONDS);
	while (gettime(MICROSECONDS) - start < usec && !simulation_finished(table))
		;
}

void	wait_all_threads(t_table *table)
{
	while (!get_bool(&table->table_mutex, &table->all_threads_ready))
		;
}

bool	all_threads_running(t_mutex *mtx, long *threads, long philo_nbr)
{
	bool	flag;

	flag = false;
	safe_mutex_handle(mtx, LOCK);
	if (*threads == philo_nbr)
		flag = true;
	safe_mutex_handle(mtx, UNLOCK);
	return (flag);
}

void	increase_val(t_mutex *mtx, long *val)
{
	safe_mutex_handle(mtx, LOCK);
	++(*val);
	safe_mutex_handle(mtx, UNLOCK);
}
