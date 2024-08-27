/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyavroya <tyavroya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:37:30 by tyavroya          #+#    #+#             */
/*   Updated: 2024/07/24 18:47:29 by tyavroya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static void	init_forks (t_philo* philo, t_fork* forks, int i)
{
	int	philo_nbr;

	philo_nbr = philo->table->philo_nbr;

	if (philo->id % 2 == 0)
	{
		philo->right_fork = &forks[(i + 1) % philo_nbr];
		philo->left_fork = &forks[i];
	}
	else
	{
		philo->left_fork = &forks[(i + 1) % philo_nbr];
		philo->right_fork = &forks[i];
	}
}

static void	philo_init (t_table *table) {
	int	i;

	i = -1;
	while (++i < table->philo_nbr)
	{
		table->philos[i].id = i + 1;
		table->philos[i].is_full = false;
		table->philos[i].meals_counter = 0;
		table->philos[i].table = table;
		init_forks(table->philos + i, table->forks, i);
	}
}

void	__init__ (t_table* table)
{
	int	i;

	i = -1;
	table->end_simulation = false;
	table->all_threads_ready = false;
	table->philos = _safe_malloc(sizeof(t_philo) * table->philo_nbr);
	table->forks = _safe_malloc(sizeof(t_fork) * table->philo_nbr);
	while (++i < table->philo_nbr)
	{
		safe_mutex_handle(&table->forks[i].mtx, INIT);
		table->forks[i].fork_id = i;
	}
	safe_mutex_handle(&table->table_mutex, INIT);
	philo_init(table);
}