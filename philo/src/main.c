/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdukic <sdukic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 19:08:12 by sdukic            #+#    #+#             */
/*   Updated: 2023/01/04 19:08:16 by sdukic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdio.h>
#include"./include/philo.h"

int	main(int argc, char **argv)
{
	t_table	table;
	t_vars	vars;

	if (check_input(argc, argv) == 0)
	{
		printf("usage: ./philo number_of_philosophers \
time_to_die time_to_eat time_to_sleep \
[number_of_times_each_philosopher_must_eat]\n");
		return (1);
	}
	if (init_table(&table, &vars, argc, argv) == 0)
		return (1);
	if (create_threads(&table, &vars) == 0)
		return (1);
	return (0);
}
