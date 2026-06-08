#include "philo.h"

int	error_msg(char *msg)
{
	printf("%s", msg);
	return (1);
}

void	destroy_all(t_data *data, int forks_count)
{
	int	i;

	i = 0;
	while (i < forks_count)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_destroy(&data->philos[i].philo_lock);
		i++;
	}
	pthread_mutex_destroy(&data->print_lock);
	pthread_mutex_destroy(&data->dead_lock);
	if (data->forks)
		free(data->forks);
	if (data->philos)
		free(data->philos);
}
