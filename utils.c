#include "philo.h"

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