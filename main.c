int	main(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (error_msg("Usage: ./philo nb_philo time_to_die "
				"time_to_eat time_to_sleep [nb_meals]\n"));
	return (0);
}
