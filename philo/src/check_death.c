/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdukic <sdukic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 18:14:20 by sdukic            #+#    #+#             */
/*   Updated: 2023/01/10 23:01:31 by sdukic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/philo.h"
#include <stdlib.h>
#include <stdio.h>

int	is_pdeath(t_philo *philo)
{
	int	time;

	time = get_time();
	pthread_mutex_lock(&philo->meal_check);
	if (time - philo->last_meal > philo->vars->rules.time_to_die)
	{
		pthread_mutex_unlock(&philo->meal_check);
		return (1);
	}
	pthread_mutex_unlock(&philo->meal_check);
	return (0);
}

int	are_all_full(t_table *table, t_vars *vars)
{
	int	i;

	i = 0;
	while (i < vars->rules.num_of_philo)
	{
		pthread_mutex_lock(&table->philos[i].state_check);
		if (table->philos[i].state != FULL)
		{
			pthread_mutex_unlock(&table->philos[i].state_check);
			return (0);
		}
		pthread_mutex_unlock(&table->philos[i].state_check);
		i++;
	}
	return (1);
}

void	kill_one_philo(t_table *table, int i)
{
	if (is_pdeath(&table->philos[i]) == 1)
		p_die(&table->philos[i]);
}

int	should_exit(t_vars *vars)
{
	pthread_mutex_lock(&vars->exit_m);
	if (vars->exit != 0)
	{
		pthread_mutex_unlock(&vars->exit_m);
		return (1);
	}
	pthread_mutex_unlock(&vars->exit_m);
	return (0);
}

void	kill_p(t_table *table, t_vars *vars)
{
	int	i;

	while (are_all_full(table, vars) == 0)
	{
		if (should_exit(vars) == 1)
			return ;
		i = 0;
		while (i < vars->rules.num_of_philo)
		{
			if (should_exit(vars) == 0)
				kill_one_philo(table, i);
			pthread_mutex_lock(&table->philos[i].meal_check);
			if (table->philos[i].num_of_meals
				== table->philos[i].vars->rules.num_of_must_eat)
			{
				pthread_mutex_lock(&table->philos[i].state_check);
				table->philos[i].state = FULL;
				pthread_mutex_unlock(&table->philos[i].state_check);
			}
			pthread_mutex_unlock(&table->philos[i].meal_check);
			i++;
		}
	}
	return ;
}
