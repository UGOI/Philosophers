/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdukic <sdukic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 19:10:55 by sdukic            #+#    #+#             */
/*   Updated: 2023/01/04 19:12:06 by sdukic           ###   ########.fr       */
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

	if ((philo->state != DEAD || override == 1) && philo->vars->deaths <= 1)
	{
		time = get_time();
		printf("%lld %d %s\n", time - philo->vars->start_time,
			philo->id, status);
	}
}

void	efficient_sleep(t_philo *philo)
{
	int	time;

	time = get_time();
	while (get_time() - time < philo->vars->rules.time_to_eat)
		usleep(50);
}
