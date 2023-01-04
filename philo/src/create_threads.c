/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdukic <sdukic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 18:18:21 by sdukic            #+#    #+#             */
/*   Updated: 2023/01/04 18:35:42 by sdukic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/time.h>
#include"./include/philo.h"

void	*routine(void *void_philosopher)
{
	int		i;
	t_philo	*philo;

	i = 0;
	philo = (t_philo *)void_philosopher;
	if (philo->id % 2)
		usleep(15000);
	while (!(philo->state == DEAD)
		&& !(philo->state == FULL) && (philo->vars->deaths == 0))
	{
		p_eat(philo);
		p_sleep(philo);
		p_think(philo);
		i++;
	}
	return (NULL);
}

int	create_threads2(pthread_t *threads, t_vars *vars, t_table *table)
{
	int	i;

	i = 0;
	while (i < vars->rules.num_of_philo)
	{
		if (pthread_create(&threads[i], NULL, &routine, &table->philos[i]) != 0)
			return (0);
		i++;
	}
	return (1);
}

int	join_threads(pthread_t *threads, t_vars *vars)
{
	int	i;

	i = 0;
	while (i < vars->rules.num_of_philo)
	{
		if (pthread_join(threads[i], NULL) != 0)
			return (0);
		i++;
	}
	return (1);
}

int	create_threads(t_table *table, t_vars *vars)
{
	pthread_t	*threads;

	threads = (pthread_t *)malloc(sizeof(pthread_t) * vars->rules.num_of_philo);
	if (threads == NULL)
		return (0);
	if (vars->rules.num_of_philo == 1)
	{
		print_status(&table->philos[0], "died", 1);
		return (0);
	}
	if (create_threads2(threads, vars, table) == 0)
		return (0);
	kill_p(table, vars);
	if (join_threads(threads, vars) == 0)
		return (0);
	free(threads);
	return (1);
}
