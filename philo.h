#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_data	t_data;

typedef enum e_state
{
	TAKE_FORK,
	EATING,
	SLEEPING,
	THINKING,
	DIED
}	t_state;

typedef struct s_philo
{
	int				id;
	long			meals_eaten;
	long			last_meal;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	philo_lock;
	t_data			*data;
}	t_philo;

struct s_data
{
	int				nb_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				must_eat;
	int				dead;
	long			start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	dead_lock;
	t_philo			*philos;
};

int		parse_args(int argc, char **argv, t_data *data);
int		init_data(t_data *data);
int		init_philos(t_data *data);
long	get_time(void);
void	ft_usleep(long ms, t_data *data);
int		ft_atoi_philo(const char *str, int *error);
void	*routine(void *arg);
int		is_dead(t_data *data);
void	*monitor(void *arg);
void	print_status(t_philo *philo, t_state state);
void	destroy_all(t_data *data, int forks_count);
int		error_msg(char *msg);

#endif
