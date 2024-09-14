/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyavroya <tyavroya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 18:34:02 by tyavroya          #+#    #+#             */
/*   Updated: 2024/09/14 18:45:21 by tyavroya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static bool	_dinner_helper(t_table *table)
{
	int	i;

	i = -1;
	table->simulation_start = gettime(MILLISECONDS);
	set_bool(&table->table_mutex, &table->all_threads_ready, true);
	if (!safe_thread_handle(&table->monitor, monitor_dinner, table, CREATE))
		return (false);
	while (++i < table->philo_nbr)
		if (!safe_thread_handle(&table->philos[i].th_philo, NULL, NULL, JOIN))
			return (false);
	set_bool(&table->table_mutex, &table->end_simulation, true);
	return (safe_thread_handle(&table->monitor, NULL, NULL, JOIN));
}

void	*dinner_simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->table);
	set_long(&philo->philo_mtx, &philo->last_meal_time, gettime(MILLISECONDS));
	increase_val(&philo->table->table_mutex, &philo->table->threads_counter);
	if (philo->id % 2 != 0)
		ft_usleep(1000, philo->table);
	while (!get_bool(&philo->philo_mtx, &philo->is_full)
		&& !simulation_finished(philo->table))
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}

bool	dinner_start(t_table *table)
{
	int	i;

	if (table->meals_nbr == 0)
		return (true);
	if (table->philo_nbr == 1)
	{
		if (!safe_thread_handle(&table->philos[0].th_philo, alone,
				&table->philos[0], CREATE))
			return (false);
	}
	else
	{
		i = -1;
		while (++i < table->philo_nbr)
			if (!safe_thread_handle(&table->philos[i].th_philo,
					dinner_simulation, &table->philos[i], CREATE))
				return (false);
	}
	return (_dinner_helper(table));
}
