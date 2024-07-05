/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyavroya <tyavroya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 20:33:29 by tyavroya          #+#    #+#             */
/*   Updated: 2024/07/05 21:27:14 by tyavroya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int main(int argc, char** argv) {
	t_table table;

	if (argc != 5 && argc != 6)
		_err("Invalid amount of arguments");

	parse(&table, argv);
}