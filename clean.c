/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhensel <flhensel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 16:07:56 by flhensel          #+#    #+#             */
/*   Updated: 2026/06/16 18:35:48 by flhensel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error_msg(char *msg)
{
	printf("%s", msg);
	return (1);
}

/* forks_count may be less than nb_philo when init_mutexes failed mid-way,
   so only the successfully initialised mutexes are destroyed. */
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
