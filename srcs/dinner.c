/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigran <tigran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 18:34:02 by tyavroya          #+#    #+#             */
/*   Updated: 2024/08/30 13:46:00 by tigran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static void	eating (t_philo* philo)
{
	safe_mutex_handle(&philo->left_fork->mtx, LOCK);
	output_simulation(philo, TAKE_FORK);
	safe_mutex_handle(&philo->right_fork->mtx, LOCK);
	output_simulation(philo, TAKE_FORK);

	set_long(&philo->philo_mtx, &philo->last_meal_time, gettime(MILLISECONDS));
	++philo->meals_counter;
	output_simulation(philo, EAT);
	ft_usleep(philo->table->time_to_eat, philo->table);
	if (philo->table->meals_nbr > 0 && philo->meals_counter == philo->table->meals_nbr)
		set_bool(&philo->philo_mtx, &philo->is_full, true);

	safe_mutex_handle(&philo->left_fork->mtx, UNLOCK);
	safe_mutex_handle(&philo->right_fork->mtx, UNLOCK);
}

static void	sleeping (t_philo* philo)
{
	output_simulation(philo, SLEEP);
	ft_usleep(philo->table->time_to_sleep, philo->table);
}

static void	thinking (t_philo* philo)
{
	output_simulation(philo, THINK);
	// ft_usleep(philo->table->time, philo->table);
}

void	*alone (void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->table);
	set_long(&philo->philo_mtx, &philo->last_meal_time, gettime(MILLISECONDS));
	increase_val(&philo->table->table_mutex, &philo->table->threads_counter);
	output_simulation(philo, TAKE_FORK);
	while (!simulation_finished(philo->table))
		usleep(get_long(&philo->table->table_mutex, &philo->table->time_to_die));
	return (NULL);
}

void	*dinner_simulation(void* data) {
	t_philo	*philo;

	philo = (t_philo*)data;

	wait_all_threads(philo->table);

	set_long(&philo->philo_mtx, &philo->last_meal_time, gettime(MILLISECONDS));

	increase_val(&philo->table->table_mutex, &philo->table->threads_counter);

	while (!get_bool(&philo->philo_mtx, &philo->is_full) && !simulation_finished(philo->table))
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}

	return NULL;
}

void dinner_start (t_table* table)
{
	int	i;

	if (table->meals_nbr == 0)
		return ;
	if (table->philo_nbr == 1)
		safe_thread_handle(&table->philos[0].th_philo, alone, &table->philos[0], CREATE);
	else
	{
		i = -1;
		while (++i < table->philo_nbr)
			safe_thread_handle(&table->philos[i].th_philo, dinner_simulation, &table->philos[i], CREATE);
	}
	table->simulation_start = gettime(MILLISECONDS);
	set_bool(&table->table_mutex, &table->all_threads_ready, true);
	safe_thread_handle(&table->monitor, monitor_dinner, table, CREATE);

	i = -1;
	while (++i < table->philo_nbr)
		safe_thread_handle(&table->philos[i].th_philo, NULL, NULL, JOIN);
	set_bool(&table->table_mutex, &table->end_simulation, true);
	safe_thread_handle(&table->monitor, NULL, NULL, JOIN);
}