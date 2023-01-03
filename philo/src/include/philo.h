#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>

enum state
{
    SLEEPING, THINKING, EATING, WAITING, DEAD, FULL
};

typedef struct rules
{
    int num_of_philo;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int num_of_must_eat;
} t_rules;

typedef struct vars
{
    int deaths;
    long long start_time;
    t_rules rules;
} t_vars;

typedef struct philo
{
    t_vars *vars;
    int id;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    long long last_meal;
    int num_of_meals;
    enum state state;
    pthread_mutex_t *meal_check;
} t_philo;


typedef struct table
{
    t_philo *philos;
    pthread_mutex_t *meal_check;
    t_rules rules;
    pthread_mutex_t *forks;
} t_table;


int is_number(char *str);
int is_all_number(char **argv);
int check_input(int argc, char **argv);
int create_threads(t_table *table);
int	ft_atoi(const char *str);
int get_time(void);
int init_table(t_table *table, t_vars *vars, int argc, char **argv);
int p_eat(t_philo *philo);
int p_sleep(t_philo *philo);
int p_think(t_philo *philo);
int is_pdeath(t_philo *philo);
void    print_status(t_philo *philo, char *status, int override);
int p_die(t_philo *philo);
void kill_p(t_table *table);
void    efficient_sleep(t_philo *philo);
#endif