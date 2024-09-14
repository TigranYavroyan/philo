/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyavroya <tyavroya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 20:33:29 by tyavroya          #+#    #+#             */
/*   Updated: 2024/09/14 18:36:35 by tyavroya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc != 5 && argc != 6)
	{
		print_with_color("Invalid amount of arguments", RED);
		return (1);
	}
	if (!parse(&table, argv) || !__init__(&table))
	{
		print_with_color("Parsing error", RED);
		return (1);
	}
	if (!dinner_start(&table))
	{
		print_with_color("Error during dinner", RED);
		_dealloc(&table);
		return (1);
	}
	_dealloc(&table);
	return (0);
}
