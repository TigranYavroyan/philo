/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyavroya <tyavroya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 17:30:19 by tyavroya          #+#    #+#             */
/*   Updated: 2024/08/29 20:33:06 by tyavroya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static bool philo_died (t_philo *philo)
{
	long	diff;
	long	time_to_die;

	if (get_bool(&philo->philo_mtx, &philo->is_full))
		return false;

	diff = gettime(MICROSECONDS) - get_long(&philo->philo_mtx, &philo->last_meal_time);
	time_to_die = philo->table->time_to_die;

	if (diff > time_to_die)
		return (true);
	return false;
}

void	*monitor_dinner (void* data)
{
	int 	i;
	t_table	*table;

	table = (t_table *) data;
	while (!all_threads_running(&table->table_mutex, &table->threads_counter, table->philo_nbr))
		;
	while (!simulation_finished(table))
	{
		i = -1;
		while (++i < table->philo_nbr && !simulation_finished(table))
		{
			if (philo_died(table->philos + i))
			{
				set_bool(&table->table_mutex, &table->end_simulation, true);
				output_simulation(table->philos + i, DIED);
			}
		}

	}

	return (NULL);
}