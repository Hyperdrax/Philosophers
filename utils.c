/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhensel <flhensel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 16:09:15 by flhensel          #+#    #+#             */
/*   Updated: 2026/06/16 18:36:10 by flhensel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* Returns current wall-clock time in milliseconds.
   1000L forces long arithmetic to prevent overflow on tv_sec (~1.7 billion). */
long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000L) + (tv.tv_usec / 1000));
}

/* Busy-waits in 200 µs steps instead of one big usleep() because usleep
   can oversleep by several ms, which would break the <10 ms death accuracy.
   Exits early when the simulation ends so threads don't stay blocked. */
void	ft_usleep(long ms, t_data *data)
{
	long	start;

	start = get_time();
	while (get_time() - start < ms)
	{
		if (is_dead(data))
			break ;
		usleep(200);
	}
}

static int	is_space(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

static int	skip_sign(const char *str, int *i, int *sign)
{
	while (is_space(str[*i]))
		(*i)++;
	if (str[*i] == '+' || str[*i] == '-')
	{
		if (str[*i] == '-')
			*sign = -1;
		(*i)++;
	}
	if (!str[*i])
		return (1);
	return (0);
}

/* Sets *error on overflow, trailing non-digits, or an empty string.
   Accumulates into long so the overflow check itself does not overflow. */
int	ft_atoi_philo(const char *str, int *error)
{
	long	res;
	int		sign;
	int		i;

	res = 0;
	sign = 1;
	i = 0;
	if (skip_sign(str, &i, &sign))
		*error = 1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + (str[i] - '0');
		if (res * sign > INT_MAX || res * sign < 0)
			*error = 1;
		i++;
	}
	if (str[i])
		*error = 1;
	return ((int)(res * sign));
}
