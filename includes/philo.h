/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyavroya <tyavroya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 17:16:29 by tyavroya          #+#    #+#             */
/*   Updated: 2024/07/08 19:05:36 by tyavroya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define NUMBER_OF_PHILOSOPHERS 1
# define TIME_TO_DIE 2
# define TIME_TO_EAT 3
# define TIME_TO_SLEEP 4
# define NUMBER_OF_TIMES_EACH_PHILOSOPHER_MUST_EAT 5

# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define SKY "\033[1;36m"
# define RESET "\033[0m"
# define MIN_TIMESTAMP 60000
# define MILLISECONDS 1000

# include <errno.h>
# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}						t_opcode;

typedef struct s_table	t_table;
typedef pthread_mutex_t	t_mutex;
typedef void			*(*t_fptr)(void *);

typedef struct s_fork
{
	t_mutex				mtx;
	int					fork_id;
}						t_fork;

typedef struct s_philo
{
	long				meals_counter;
	long				last_meal_time;
	int					id;
	bool				is_full;
	t_fork				*left_fork;
	t_fork				*right_fork;
	pthread_t			th_philo;
	t_table				*table;
}						t_philo;

struct					s_table
{
	long				philo_nbr;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				meals_nbr;
	long				simulation_start;
	bool				end_simulation;
	t_fork				*forks;
	t_philo				*philos;
};

// init.c
void					__init__(t_table *table);

// exit.c
void					_err(const char *msg);
void					_dealloc(t_table *table);

// helpers.c
bool					is_digit(char ch);
bool					is_whitespace(char ch);
int						ft_strlen(const char *str);
void					print_with_color(const char *msg, const char *color);

// parsing.c
long					ft_atol(const char *str);
void					parse(t_table *table, char **argv);

// safe functions.c
void					*__attribute__((malloc,
								warn_unused_result)) _safe_malloc(size_t bytes);
void					_safe_mutex_handle(t_mutex *mtx, t_opcode opcode);
void					safe_thread_handle(pthread_t *thread, t_fptr foo,
							void *data, t_opcode code);

#endif // PHILO_H