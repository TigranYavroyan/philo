/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyavroya <tyavroya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 17:30:19 by tyavroya          #+#    #+#             */
/*   Updated: 2024/08/29 19:22:18 by tyavroya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	*monitor_dinner (void* data)
{
	t_table	*table;

	table = (t_table *) data;
	while (!all_threads_running(&table->table_mutex, &table->threads_counter, table->philo_nbr))
		;

	return (NULL);
}