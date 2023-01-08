/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdukic <sdukic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 18:00:51 by sdukic            #+#    #+#             */
/*   Updated: 2023/01/08 22:38:17 by sdukic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>

enum	e_state
{
	THINKING,
	DEAD,
	FULL
};

typedef struct rules
{
	int	num_of_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	num_of_must_eat;
}	t_rules;

typedef struct vars
{
	int				deaths;
	long long		start_time;
	t_rules			rules;
}	t_vars;

typedef struct philo
{
	t_vars			*vars;
	int				id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	meal_check;
	pthread_mutex_t	state_check;
	long long		last_meal;
	int				num_of_meals;
	enum e_state	state;
}	t_philo;

typedef struct table
{
	t_philo			*philos;
	pthread_mutex_t	*forks;
}	t_table;

int		is_number(char *str);
int		is_all_number(char **argv);
int		check_input(int argc, char **argv);
int		create_threads(t_table *table, t_vars *vars);
int		ft_atoi(const char *str);
int		get_time(void);
int		init_table(t_table *table, t_vars *vars, int argc, char **argv);
int		p_eat(t_philo *philo);
int		p_sleep(t_philo *philo);
int		p_think(t_philo *philo);
int		is_pdeath(t_philo *philo);
void	print_status(t_philo *philo, char *status, int override);
int		p_die(t_philo *philo);
void	kill_p(t_table *table, t_vars *vars);
void	efficient_sleep(t_philo *philo);
void	free_all(t_table *table, t_vars *vars);
#endif
