/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhensel <flhensel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 16:08:33 by flhensel          #+#    #+#             */
/*   Updated: 2026/06/16 18:36:01 by flhensel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_values(t_data *data, int argc)
{
	if (data->nb_philo <= 0 || data->nb_philo > 200)
		return (error_msg("Error: number of philosophers must be 1-200\n"));
	if (data->time_to_die < 0 || data->time_to_eat < 0
		|| data->time_to_sleep < 0)
		return (error_msg("Error: times must be positive\n"));
	if (argc == 6 && data->must_eat <= 0)
		return (error_msg("Error: must_eat must be positive\n"));
	return (0);
}

/* must_eat is set to -1 when the optional 5th argument is omitted,
   signalling the monitor that there is no meal-count stop condition. */
int	parse_args(int argc, char **argv, t_data *data)
{
	int	error;

	error = 0;
	data->nb_philo = ft_atoi_philo(argv[1], &error);
	data->time_to_die = ft_atoi_philo(argv[2], &error);
	data->time_to_eat = ft_atoi_philo(argv[3], &error);
	data->time_to_sleep = ft_atoi_philo(argv[4], &error);
	if (argc == 6)
		data->must_eat = ft_atoi_philo(argv[5], &error);
	else
		data->must_eat = -1;
	if (error)
		return (error_msg("Error: arguments must be valid integers\n"));
	if (check_values(data, argc))
		return (1);
	return (0);
}
