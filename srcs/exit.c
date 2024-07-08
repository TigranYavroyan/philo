/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyavroya <tyavroya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 20:24:14 by tyavroya          #+#    #+#             */
/*   Updated: 2024/07/08 19:26:22 by tyavroya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	_dealloc(t_table *table)
{
	free(table->philos);
	free(table->forks);
}

void	_err(const char *msg)
{
	print_with_color(msg, RED);
	exit(EXIT_FAILURE);
}