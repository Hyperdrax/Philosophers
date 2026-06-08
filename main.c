#include "philo.h"

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
	return (0);
}
