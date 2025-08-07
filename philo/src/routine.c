/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 16:38:41 by gojeda            #+#    #+#             */
/*   Updated: 2025/08/07 21:03:12 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	safe_print(t_philo *philo, char *msg)
{
	long	timestamp;

	pthread_mutex_lock(&philo->rules->print_mutex);
	if (!has_someone_died(philo->rules))
	{
		timestamp = get_time_in_ms() - philo->rules->start_time;
		printf("%ld %d %s\n", timestamp, philo->id, msg);
	}
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
		usleep(100);
	}
}

static void	philo_cicle(t_philo	*philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		safe_print(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		safe_print(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		safe_print(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		safe_print(philo, "has taken a fork");
	}
	pthread_mutex_lock(&philo->last_meal_mutex);
	philo->last_meal = get_time_in_ms();
	pthread_mutex_unlock(&philo->last_meal_mutex);
	safe_print(philo, "is_eating");
	ft_usleep(philo->rules->time_to_eat, philo->rules);
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	safe_print(philo, "is sleaping");
	ft_usleep(philo->rules->time_to_sleep, philo->rules);
	safe_print(philo, "is thinking");
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(100);
	while (!has_someone_died(philo->rules))
	{
		philo_cicle(philo);
		philo->meals_eaten++;
		if (philo->rules->must_eat_count != -1
			&& philo->meals_eaten == philo->rules->must_eat_count)
		{
			pthread_mutex_lock(&philo->rules->full_mutex);
			philo->rules->full_philos++;
			pthread_mutex_unlock(&philo->rules->full_mutex);
		}
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
			pthread_mutex_lock(&philos[i].last_meal_mutex);
			time_since_meal = get_time_in_ms() - philos[i].last_meal;
			pthread_mutex_unlock(&philos[i].last_meal_mutex);
			if (time_since_meal >= rules->time_to_die)
				return (control_someone_died(rules, philos, i), NULL);
			i++;
		}
		if (!has_eating_enough(rules))
			return (NULL);
		usleep(100);
	}
	return (NULL);
}
