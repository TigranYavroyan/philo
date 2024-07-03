/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyavroya <tyavroya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 17:16:29 by tyavroya          #+#    #+#             */
/*   Updated: 2024/07/03 18:22:35 by tyavroya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define NUMBER_OF_PHILOSOPHERS 1
# define TIME_TO_DIE 2
# define TIME_TO_EAT 3
# define TIME_TO_SLEEP 4
# define NUMBER_OF_TIMES_EACH_PHILOSOPHER_MUST_EAT 5

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_table t_table;

typedef struct s_fork
{
	pthread_mutex_t	mtx;
	int				fork_id;
}					t_fork;

typedef struct s_philo
{
	long			meals_counter;
	long			last_meal_time;
	int				id;
	bool			is_full;
	t_fork			*left_fork;
	t_fork			*right_fork;
	pthread_t		th_philo;
	t_table			*table;
}					t_philo;

struct s_table
{
	long			philo_nbr;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			meals_nbr;
	long			simulation_start;
	bool			end_simulation;
	t_fork			*forks;
	t_philo			*philos;
};

#endif // PHILO_H