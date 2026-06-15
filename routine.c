#include "philo.h"

static void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, TAKE_FORK);
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, TAKE_FORK);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, TAKE_FORK);
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, TAKE_FORK);
	}
}

static void	eat(t_philo *philo)
{
	take_forks(philo);
	pthread_mutex_lock(&philo->philo_lock);
	philo->last_meal = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->philo_lock);
	print_status(philo, EATING);
	ft_usleep(philo->data->time_to_eat, philo->data);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

static void	think(t_philo *philo)
{
	long	think_time;

	print_status(philo, THINKING);
	if (philo->data->nb_philo % 2 == 0)
		return ;
	think_time = philo->data->time_to_eat;
	ft_usleep(think_time, philo->data);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->nb_philo == 1)
	{
		print_status(philo, TAKE_FORK);
		ft_usleep(philo->data->time_to_die, philo->data);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		ft_usleep(philo->data->time_to_eat, philo->data);
	while (!is_dead(philo->data))
	{
		eat(philo);
		print_status(philo, SLEEPING);
		ft_usleep(philo->data->time_to_sleep, philo->data);
		think(philo);
	}
	return (NULL);
}
