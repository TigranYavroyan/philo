/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigran <tigran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 20:24:14 by tyavroya          #+#    #+#             */
/*   Updated: 2024/08/30 13:29:34 by tigran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	_dealloc(t_table *table)
{
	t_philo	*philo;
	int		i;

	i = -1;
	while (++i < table->philo_nbr)
	{
		philo = table->philos + i;
		safe_mutex_handle(&philo->philo_mtx, DESTROY);
	}
	safe_mutex_handle(&table->o_mtx, DESTROY);
	safe_mutex_handle(&table->table_mutex, DESTROY);
	free(table->forks);
	free(table->philos);
}

void	_err(const char *msg)
{
	print_with_color(msg, RED);
	exit(EXIT_FAILURE);
}