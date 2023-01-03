#include"./include/philo.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int p_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, "has taken a fork", 0);
	pthread_mutex_lock(philo->right_fork);
	print_status(philo, "has taken a fork", 0);
	pthread_mutex_lock(philo->meal_check);
	print_status(philo, "is eating", 0);
	philo->last_meal = get_time();
	pthread_mutex_unlock(philo->meal_check);
	efficient_sleep(philo);
	(philo->num_of_meals)++;
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
    return (1);
}

int p_sleep(t_philo *philo)
{
    print_status(philo, "is sleeping", 0);
    efficient_sleep(philo);
    return (1);
}

int p_think(t_philo *philo)
{
    print_status(philo, "is thinking", 0);
    return (1);
}

int p_die(t_philo *philo)
{
    if (philo->state != DEAD)
        philo->vars->deaths++;
    philo->state = DEAD;
    print_status(philo, "died", 1);
    
    return (1);
}