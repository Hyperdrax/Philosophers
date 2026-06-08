#include "philo.h"

static int	init_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (1);
		i++;
	}
	if (pthread_mutex_init(&data->print_lock, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&data->dead_lock, NULL) != 0)
		return (1);
	return (0);
}

int	init_data(t_data *data)
{
	data->dead = 0;
	data->start_time = 0;
	data->philos = NULL;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->forks)
		return (error_msg("Error: malloc failed\n"));
	if (init_mutexes(data))
	{
		free(data->forks);
		return (error_msg("Error: mutex init failed\n"));
	}
	return (0);
}
