/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhensel <flhensel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 16:08:24 by flhensel          #+#    #+#             */
/*   Updated: 2026/06/16 18:35:58 by flhensel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* Always read data->dead through this function so the lock is never skipped. */
int	is_dead(t_data *data)
{
	int	dead;

	pthread_mutex_lock(&data->dead_lock);
	dead = data->dead;
	pthread_mutex_unlock(&data->dead_lock);
	return (dead);
}

static void	set_dead(t_data *data)
{
	pthread_mutex_lock(&data->dead_lock);
	data->dead = 1;
	pthread_mutex_unlock(&data->dead_lock);
}

/* philo_lock is held while reading last_meal to avoid a race with the
   philosopher thread that writes last_meal inside eat(). */
static int	check_starvation(t_data *data, int i)
{
	long	time_since_meal;

	pthread_mutex_lock(&data->philos[i].philo_lock);
	time_since_meal = get_time() - data->philos[i].last_meal;
	if (time_since_meal > data->time_to_die)
	{
		pthread_mutex_unlock(&data->philos[i].philo_lock);
		set_dead(data);
		print_status(&data->philos[i], DIED);
		return (1);
	}
	pthread_mutex_unlock(&data->philos[i].philo_lock);
	return (0);
}

static int	all_ate_enough(t_data *data)
{
	int	i;
	int	full;

	if (data->must_eat == -1)
		return (0);
	i = 0;
	full = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_lock(&data->philos[i].philo_lock);
		if (data->philos[i].meals_eaten >= data->must_eat)
			full++;
		pthread_mutex_unlock(&data->philos[i].philo_lock);
		i++;
	}
	if (full == data->nb_philo)
	{
		set_dead(data);
		return (1);
	}
	return (0);
}

/* Sweeps every philosopher every 0.5 ms to detect death or full satiation. */
void	*monitor(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (1)
	{
		i = 0;
		while (i < data->nb_philo)
		{
			if (check_starvation(data, i))
				return (NULL);
			i++;
		}
		if (all_ate_enough(data))
			return (NULL);
		usleep(500);
	}
	return (NULL);
}
