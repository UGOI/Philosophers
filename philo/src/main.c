/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdukic <sdukic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 19:08:12 by sdukic            #+#    #+#             */
/*   Updated: 2023/01/05 18:43:05 by sdukic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdio.h>
#include"./include/philo.h"
#include<stdlib.h>

void	free_all(t_table *table, t_vars *vars)
{
	int	i;

	i = 0;
	while (i < vars->rules.num_of_philo)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	pthread_mutex_destroy(vars->meal_check);
	free(vars->meal_check);
	free(table->forks);
	free(table->philos);
	return ;
}

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
	free_all(&table, &vars);
	return (0);
}
