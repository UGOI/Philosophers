#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/time.h>
#include"./include/philo.h"

void *routine(void *void_philosopher)
{
    int				i;
	t_philo     	*philo;

	i = 0;
	philo = (t_philo *)void_philosopher;
	if (philo->id % 2)
		usleep(15000);
	while (!(philo->state == DEAD) && !(philo->state == FULL) && (philo->vars->deaths == 0))
	{
		p_eat(philo);
        p_sleep(philo);
		p_think(philo);
		i++;
	}
	return (NULL);
}

int create_threads(t_table *table, t_vars *vars)
{
    int i;
    pthread_t *threads;

    threads = (pthread_t *)malloc(sizeof(pthread_t) * vars->rules.num_of_philo);
    if (threads == NULL)
        return (0);
    if (vars->rules.num_of_philo == 1)
    {
        print_status(&table->philos[0], "died", 1);
        return (0);
    }
    i = 0;
    while (i < vars->rules.num_of_philo)
    {
        if (pthread_create(&threads[i], NULL, &routine, &table->philos[i]) != 0)
            return (0);
        i++;
    }
    kill_p(table, vars);
    i = 0;
    while (i < vars->rules.num_of_philo)
    {
        if (pthread_join(threads[i], NULL) != 0)
            return (0);
        i++;
    }
    free(threads);
    return (1);
}