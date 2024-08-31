/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyavroya <tyavroya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 16:17:06 by tyavroya          #+#    #+#             */
/*   Updated: 2024/08/31 18:25:52 by tyavroya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	eating(t_philo *philo)
{
	safe_mutex_handle(&philo->left_fork->mtx, LOCK);
	output_simulation(philo, TAKE_FORK);
	safe_mutex_handle(&philo->right_fork->mtx, LOCK);
	output_simulation(philo, TAKE_FORK);
	set_long(&philo->philo_mtx, &philo->last_meal_time, gettime(MILLISECONDS));
	++philo->meals_counter;
	output_simulation(philo, EAT);
	ft_usleep(philo->table->time_to_eat, philo->table);
	if (philo->table->meals_nbr > 0
		&& philo->meals_counter == philo->table->meals_nbr)
		set_bool(&philo->philo_mtx, &philo->is_full, true);
	safe_mutex_handle(&philo->left_fork->mtx, UNLOCK);
	safe_mutex_handle(&philo->right_fork->mtx, UNLOCK);
}

void	sleeping(t_philo *philo)
{
	output_simulation(philo, SLEEP);
	ft_usleep(philo->table->time_to_sleep, philo->table);
}

void	thinking(t_philo *philo)
{
	output_simulation(philo, THINK);
}

void	*alone(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->table);
	set_long(&philo->philo_mtx, &philo->last_meal_time, gettime(MILLISECONDS));
	increase_val(&philo->table->table_mutex, &philo->table->threads_counter);
	output_simulation(philo, TAKE_FORK);
	while (!simulation_finished(philo->table))
		usleep(get_long(&philo->table->table_mutex,
				&philo->table->time_to_die));
	return (NULL);
}
