/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyavroya <tyavroya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 18:34:02 by tyavroya          #+#    #+#             */
/*   Updated: 2024/08/27 15:15:26 by tyavroya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	*dinner_simulation(void* data) {
	t_philo	*philo;

	philo = (t_philo*)data;

	wait_all_threads(philo->table);

	while (!simulation_finished(philo->table))
	{
		if (philo->is_full)
			break;

		// eat();
		// sleep();
		// think();
	}

	return NULL;
}

void dinner_start (t_table* table)
{
	int	i;

	if (table->meals_nbr == 0)
		return ;
	if (table->philo_nbr == 1)
		;
	else
	{
		i = -1;
		while (++i < table->philo_nbr)
			safe_thread_handle(&table->philos[i].th_philo, dinner_simulation, &table->philos[i], CREATE);
	}
	table->simulation_start = gettime(MILLISECONDS);

	set_bool(&table->table_mutex, &table->all_threads_ready, true);

	i = -1;
	while (++i < table->philo_nbr)
		safe_thread_handle(&table->philos[i].th_philo, NULL, NULL, JOIN);
}