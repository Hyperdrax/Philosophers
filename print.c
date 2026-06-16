/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhensel <flhensel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 16:08:57 by flhensel          #+#    #+#             */
/*   Updated: 2026/06/16 18:36:04 by flhensel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* The is_dead check inside the lock prevents any state message from
   slipping in between the DIED print and the dead flag being set. */
void	print_status(t_philo *philo, t_state state)
{
	long	timestamp;

	pthread_mutex_lock(&philo->data->print_lock);
	if (is_dead(philo->data) && state != DIED)
	{
		pthread_mutex_unlock(&philo->data->print_lock);
		return ;
	}
	timestamp = get_time() - philo->data->start_time;
	if (state == TAKE_FORK)
		printf("%ld %d has taken a fork\n", timestamp, philo->id);
	else if (state == EATING)
		printf("%ld %d is eating\n", timestamp, philo->id);
	else if (state == SLEEPING)
		printf("%ld %d is sleeping\n", timestamp, philo->id);
	else if (state == THINKING)
		printf("%ld %d is thinking\n", timestamp, philo->id);
	else if (state == DIED)
		printf("%ld %d died\n", timestamp, philo->id);
	pthread_mutex_unlock(&philo->data->print_lock);
}
