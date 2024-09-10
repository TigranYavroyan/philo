/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigran <tigran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:37:30 by tyavroya          #+#    #+#             */
/*   Updated: 2024/09/10 23:54:00 by tigran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static void	init_forks(t_philo *philo, t_fork *forks, int i)
{
	int	philo_nbr;

	philo_nbr = philo->table->philo_nbr;
	if (philo->id % 2 == 0)
	{
		philo->left_fork = &forks[(i + 1) % philo_nbr];
		philo->right_fork = &forks[i];
	}
	else
	{
		philo->left_fork = &forks[(i + 1) % philo_nbr];
		philo->right_fork = &forks[i];
	}
}

static bool	philo_init(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->philo_nbr)
	{
		table->philos[i].id = i + 1;
		table->philos[i].is_full = false;
		table->philos[i].meals_counter = 0;
		table->philos[i].table = table;
		init_forks(table->philos + i, table->forks, i);
		if (!safe_mutex_handle(&table->philos[i].philo_mtx, INIT))
			return (false);
	}
	return (true);
}

bool	__init__(t_table *table)
{
	int	i;

	i = -1;
	table->end_simulation = false;
	table->threads_counter = 0;
	table->all_threads_ready = false;
	table->philos = malloc(sizeof(t_philo) * table->philo_nbr);
	if (table->philos == NULL)
		return (false);
	table->forks = malloc(sizeof(t_fork) * table->philo_nbr);
	if (table->forks == NULL)
		return (false);
	while (++i < table->philo_nbr)
	{
		if (!safe_mutex_handle(&table->forks[i].mtx, INIT))
			return (false);
		table->forks[i].fork_id = i;
	}
	if (!safe_mutex_handle(&table->table_mutex, INIT))
		return (false);
	if (!philo_init(table) || !safe_mutex_handle(&table->o_mtx, INIT))
		return (false);
	return (true);
}
