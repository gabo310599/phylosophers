/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 11:49:12 by gojeda            #+#    #+#             */
/*   Updated: 2025/08/07 20:38:34 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (*str)
	{
		len++;
		str++;
	}
	return (len);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	sign;
	int	result;

	sign = 1;
	result = 0;
	i = 0;
	while (nptr[i] && (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13)))
		i++;
	if (nptr[i] && (nptr[i] == '-' || nptr[i] == '+'))
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (nptr[i] && (nptr[i] >= '0' && nptr[i] <= '9'))
	{
		result = result * 10 + (nptr[i] - '0');
		i++;
	}
	return (result * sign);
}

long	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000L) + (tv.tv_usec / 1000));
}

void	print_error(char *msg)
{
	write(2, "Error: ", 7);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
}

void	destroy_mutex(t_philo *philos, int count, t_rules *rules)
{
	int	i;

	if (philos)
	{
		i = 0;
		while (i < count)
		{
			pthread_mutex_destroy(&philos[i].last_meal_mutex);
			i++;
		}
		free(philos);
	}
	if (rules && rules->forks)
	{
		i = 0;
		while (i < count)
		{
			pthread_mutex_destroy(&rules->forks[i]);
			i++;
		}
		pthread_mutex_destroy(&rules->print_mutex);
		pthread_mutex_destroy(&rules->death_mutex);
		pthread_mutex_destroy(&rules->full_mutex);
		free(rules->forks);
	}
}
