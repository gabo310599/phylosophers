/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 16:25:39 by gojeda            #+#    #+#             */
/*   Updated: 2025/08/05 17:56:09 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

t_philo	*init_philos(t_rules *rules)
{
	t_philo	*philos;
	int		i;

	philos = malloc(sizeof(t_philo) * rules->philo_count);
	if (!philos)
		return (NULL);
	i = 0;
	while (i < rules->philo_count)
	{
		philos[i].id = i + 1;
		philos[i].meals_eaten = 0;
		philos[i].last_meal = rules->start_time;
		philos[i].rules = rules;
		philos[i].left_fork = &rules->forks[i];
		philos[i].right_fork = &rules->forks[(i + 1) % rules->philo_count];
		i++;
	}
	return (philos);
}

int	init_mutexes(t_rules *rules)
{
	int	i;

	rules->forks = malloc(sizeof(pthread_mutex_t) * rules->philo_count);
	if (!rules->forks)
		return (print_error("Malloc fallo en forks"), 0);
	i = 0;
	while (i < rules->philo_count)
	{
		if (pthread_mutex_init(&rules->forks[i], NULL) != 0)
			return (print_error("Fallo al inicialiar fork mutex"), 0);
		i++;
	}
	if (pthread_mutex_init(&rules->print_mutex, NULL) != 0)
		return (print_error("Fallos al inicializar print mutex"), 0);
	if (pthread_mutex_init(&rules->death_mutex, NULL) != 0)
		return (print_error("Fallo al inicializar death mutex"), 0);
	return (1);
}
