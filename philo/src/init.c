#include "./include/philo.h"
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

int init_table(t_table *table, t_vars *vars, int argc, char **argv)
{
    int i;

    vars->rules.num_of_philo = ft_atoi(argv[1]);
    vars->rules.time_to_die = ft_atoi(argv[2]);
    vars->rules.time_to_eat = ft_atoi(argv[3]);
    vars->rules.time_to_sleep = ft_atoi(argv[4]);
    vars->deaths = 0;
    if (argc == 6)
        vars->rules.num_of_must_eat = ft_atoi(argv[5]);
    else
        vars->rules.num_of_must_eat = -1;
    table->philos = (t_philo *)malloc(sizeof(t_philo) * vars->rules.num_of_philo);
    if (table->philos == NULL)
        return (0);
    table->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * vars->rules.num_of_philo);
    if (table->forks == NULL)
        return (0);
    i = 0;
    while (i < vars->rules.num_of_philo)
    {
        if (pthread_mutex_init(&table->forks[i], NULL) != 0)
            return (0);
        
        i++;
    }
    vars->meal_check = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
    if (vars->meal_check == NULL)
        return (0);
    if (pthread_mutex_init(vars->meal_check, NULL) != 0)
        return (0);
    i = 0;
    vars->start_time = get_time();
    while (i < vars->rules.num_of_philo)
    {
        table->philos[i].id = i + 1;
        table->philos[i].left_fork = &table->forks[i];
        table->philos[i].right_fork = &table->forks[(i + 1) % vars->rules.num_of_philo];
        table->philos[i].last_meal = vars->start_time;
        table->philos[i].num_of_meals = 0;
        table->philos[i].state = THINKING;
        table->philos[i].vars = vars;
        table->philos[i].vars->rules = vars->rules;
        i++;
    }
    return (1);
}