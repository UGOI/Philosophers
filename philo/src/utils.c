/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdukic <sdukic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 19:10:55 by sdukic            #+#    #+#             */
/*   Updated: 2023/01/07 20:54:25 by sdukic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/philo.h"
#include<sys/time.h>
#include<stdio.h>
#include<unistd.h>

int	get_time(void)
{
	struct timeval	tv;
	struct timezone	tz;

	gettimeofday(&tv, &tz);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	print_status(t_philo *philo, char *status, int override)
{
	int	time;

	pthread_mutex_lock(&philo->vars->print);
	pthread_mutex_lock(&philo->state_check);
	pthread_mutex_lock(&philo->vars->exit_m);
	if (((philo->state != DEAD && philo->vars->exit == 0) || override == 1))
	{
		pthread_mutex_unlock(&philo->vars->exit_m);
		pthread_mutex_unlock(&philo->state_check);
		time = get_time();
		printf("%lld %d %s\n", time - philo->vars->start_time,
			philo->id, status);
	}
	else
	{
		pthread_mutex_unlock(&philo->vars->exit_m);
		pthread_mutex_unlock(&philo->state_check);
	}
	pthread_mutex_unlock(&philo->vars->print);
}

void	efficient_sleep(t_philo *philo)
{
	int	time;

	time = get_time();
	while (get_time() - time < philo->vars->rules.time_to_eat)
		usleep(50);
}
