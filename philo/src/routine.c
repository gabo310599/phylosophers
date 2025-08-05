/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 16:38:41 by gojeda            #+#    #+#             */
/*   Updated: 2025/08/05 18:49:03 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	safe_print(t_philo *philo, char *msg)
{
	long	timestamp;

	pthread_mutex_lock(&philo->rules->print_mutex);
	timestamp = get_time_in_ms() - philo->rules->start_time;
	printf("%ld %d %s\n", timestamp, philo->id, msg);
	pthread_mutex_unlock(&philo->rules->print_mutex);
}

void	ft_usleep(long duration, t_rules *rules)
{
	long	start;

	start = get_time_in_ms();
	while ((get_time_in_ms() - start) < duration)
	{
		if (has_someone_died(rules))
			break ;
		usleep(500);
	}
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(100);
	while (!has_someone_died(philo->rules))
	{
		if (has_someone_died(philo->rules))
			break ;
		pthread_mutex_lock(philo->left_fork);
		safe_print(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		safe_print(philo, "has taken a fork");
		safe_print(philo, "is_eating");
		philo->last_meal = get_time_in_ms();
		ft_usleep(philo->rules->time_to_eat, philo->rules);
		philo->meals_eaten++;
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		safe_print(philo, "is sleaping");
		ft_usleep(philo->rules->time_to_sleep, philo->rules);
		safe_print(philo, "is thinking");
	}
	return (NULL);
}

void	*monitor_routine(void *arg)
{
	t_philo	*philos;
	t_rules	*rules;
	int		i;
	long	time_since_meal;

	philos = (t_philo *)arg;
	rules = philos[0].rules;
	while (!has_someone_died(rules))
	{
		i = 0;
		while (i < rules->philo_count && !has_someone_died(rules))
		{
			time_since_meal = get_time_in_ms() - philos[i].last_meal;
			if (time_since_meal >= rules->time_to_die)
			{
				control_someone_died(rules, philos, i);
				break ;
			}
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}
