/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyavroya <tyavroya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 16:00:33 by tyavroya          #+#    #+#             */
/*   Updated: 2024/08/31 16:08:26 by tyavroya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	output_simulation(t_philo *philo, t_print_code print_code)
{
	long	time;

	time = gettime(MILLISECONDS) - philo->table->simulation_start;
	safe_mutex_handle(&philo->table->o_mtx, LOCK);
	if (!simulation_finished(philo->table))
	{
		if (print_code == TAKE_FORK)
			printf("%ld %d has taken a fork\n", time, philo->id);
		else if (print_code == EAT)
			printf("%s%ld %d is eating %s\n", SKY, time, philo->id, RESET);
		else if (print_code == SLEEP)
			printf("%ld %d is sleeping\n", time, philo->id);
		else if (print_code == THINK)
			printf("%ld %d is thinking\n", time, philo->id);
		else if (print_code == DIED)
			printf("%ld %d died\n", time, philo->id);
		else
			_err("Invalid opcode for output simulation");
	}
	safe_mutex_handle(&philo->table->o_mtx, UNLOCK);
}
