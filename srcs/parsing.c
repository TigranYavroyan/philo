/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigran <tigran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 20:09:51 by tyavroya          #+#    #+#             */
/*   Updated: 2024/09/11 00:02:24 by tigran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static const char	*valid_str(const char *str)
{
	while (is_whitespace(*str))
		++str;
	if (*str == '+')
		++str;
	else if (*str == '-')
		return (NULL);
	if (!is_digit(*str))
		return (NULL);
	return (str);
}

long	ft_atol(const char *str)
{
	int		len;
	long	num;

	num = 0;
	len = 0;
	str = valid_str(str);
	if (str == NULL)
		return (-1);
	while (is_digit(*str))
	{
		num = (num * 10) + (*str - '0');
		++str;
		++len;
	}
	if (len > 10 || num > INT_MAX)
		return (-1);
	return (num);
}

bool	parse(t_table *table, char **argv)
{
	table->philo_nbr = ft_atol(argv[1]);
	table->time_to_die = ft_atol(argv[2]) * 1e3;
	table->time_to_eat = ft_atol(argv[3]) * 1e3;
	table->time_to_sleep = ft_atol(argv[4]) * 1e3;
	if (table->time_to_die < MIN_TIMESTAMP || table->time_to_eat < MIN_TIMESTAMP
		|| table->time_to_sleep < MIN_TIMESTAMP)
		return (false);
	if (table->philo_nbr > 200 || table->philo_nbr == -1)
		return (false);
	if (argv[5])
		table->meals_nbr = ft_atol(argv[5]);
	else
		table->meals_nbr = -1;
	return (true);
}
