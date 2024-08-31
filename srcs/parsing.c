/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyavroya <tyavroya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 20:09:51 by tyavroya          #+#    #+#             */
/*   Updated: 2024/08/31 16:08:33 by tyavroya         ###   ########.fr       */
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
		_err("The number must be positive");
	if (!is_digit(*str))
		_err("The number is not valid");
	return (str);
}

long	ft_atol(const char *str)
{
	int		len;
	long	num;

	num = 0;
	len = 0;
	str = valid_str(str);
	while (is_digit(*str))
	{
		num = (num * 10) + (*str - '0');
		++str;
		++len;
	}
	if (len > 10 || num > INT_MAX)
		_err("The number is not valid");
	return (num);
}

void	parse(t_table *table, char **argv)
{
	table->philo_nbr = ft_atol(argv[1]);
	table->time_to_die = ft_atol(argv[2]) * 1e3;
	table->time_to_eat = ft_atol(argv[3]) * 1e3;
	table->time_to_sleep = ft_atol(argv[4]) * 1e3;
	if (table->time_to_die < MIN_TIMESTAMP || table->time_to_eat < MIN_TIMESTAMP
		|| table->time_to_sleep < MIN_TIMESTAMP)
		_err("The timestamps must be larger than 60 milliseconds");
	if (table->philo_nbr > 200 || table->philo_nbr == 0)
		_err("The philo number must be (0 < n < 200)");
	if (argv[5])
		table->meals_nbr = ft_atol(argv[5]);
	else
		table->meals_nbr = -1;
}
