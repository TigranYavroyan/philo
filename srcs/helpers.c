/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyavroya <tyavroya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 20:24:59 by tyavroya          #+#    #+#             */
/*   Updated: 2024/07/08 16:29:01 by tyavroya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

bool	is_digit(char ch)
{
	return (ch >= '0' && ch <= '9');
}

bool	is_whitespace(char ch)
{
	return (ch == ' ' || ch == '\t' || ch == '\r' || ch == '\n' || ch == '\v'
		|| ch == '\f');
}

int	ft_strlen(const char *str)
{
	int	count;

	count = 0;
	while (str && *str)
	{
		++count;
		++str;
	}
	return (count);
}

void	print_with_color(const char *msg, const char *color)
{
	printf("%s%s%s\n", color, msg, RESET);
}