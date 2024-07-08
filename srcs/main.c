/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyavroya <tyavroya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 20:33:29 by tyavroya          #+#    #+#             */
/*   Updated: 2024/07/08 19:36:45 by tyavroya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	main(int argc, char **argv)
{
	t_table table;

	// while (true) {
	// 	_safe_malloc(10000000);
	// }

	if (argc != 5 && argc != 6)
		_err("Invalid amount of arguments");

	parse(&table, argv);
	__init__(&table);
	_dealloc(&table);
}

void __attribute__((destructor)) __exit__ () {
	system("leaks philo");
}