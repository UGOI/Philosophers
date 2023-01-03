#include "./include/philo.h"
#include <stdlib.h>
#include <stdio.h>

int is_pdeath(t_philo *philo)
{
    int time;

    time = get_time();
    if (time - philo->last_meal > philo->vars->rules.time_to_die)
    {
        return (1);
    }
    return (0);
}

int are_all_dead(t_table *table)
{
    int i;

    i = 0;
    while (i < table->rules.num_of_philo)
    {
        if (table->philos[i].state != DEAD)
        {
            return (0);
        }
        i++;
    }
    return (1);
}

int are_all_full(t_table *table)
{
    int i;

    i = 0;
    while (i < table->rules.num_of_philo)
    {
        if (table->philos[i].state != FULL)
        {
            return (0);
        }
        i++;
    }
    return (1);
}

void kill_p(t_table *table)
{
    int i;

    while (are_all_dead(table) == 0 && are_all_full(table) == 0)
    {
        i = 0;
        while (i < table->rules.num_of_philo)
        {
            pthread_mutex_lock(table->philos[i].meal_check);
            if (table->philos[i].state != DEAD)
            {   
                if (is_pdeath(&table->philos[i]) == 1)
                {
                    p_die(&table->philos[i]);
                }
            }
            if (table->philos[i].num_of_meals == table->philos[i].vars->rules.num_of_must_eat)
            {
                table->philos[i].state = FULL;
            }
            pthread_mutex_unlock(table->philos[i].meal_check);
            i++;
        }
    }
    return ;
}