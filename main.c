#include "philo.h"

static int	start_threads(t_data *data)
{
	int			i;
	pthread_t	mon;

	data->start_time = get_time();
	i = 0;
	while (i < data->nb_philo)
	{
		data->philos[i].last_meal = data->start_time;
		if (pthread_create(&data->philos[i].thread, NULL,
				routine, &data->philos[i]) != 0)
			return (error_msg("Error: thread creation failed\n"));
		i++;
	}
	if (pthread_create(&mon, NULL, monitor, data) != 0)
		return (error_msg("Error: thread creation failed\n"));
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
	pthread_join(mon, NULL);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 5 && argc != 6)
		return (error_msg("Usage: ./philo nb_philo time_to_die "
				"time_to_eat time_to_sleep [nb_meals]\n"));
	if (parse_args(argc, argv, &data))
		return (1);
	if (init_data(&data))
		return (1);
	if (init_philos(&data))
	{
		destroy_all(&data, data.nb_philo);
		return (1);
	}
	if (start_threads(&data))
	{
		destroy_all(&data, data.nb_philo);
		return (1);
	}
	destroy_all(&data, data.nb_philo);
	return (0);
}
