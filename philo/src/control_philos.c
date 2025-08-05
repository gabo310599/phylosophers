/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_philos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 17:34:37 by gojeda            #+#    #+#             */
/*   Updated: 2025/08/05 18:29:42 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	has_someone_died(t_rules *rules)
{
	int	dead;

	pthread_mutex_lock(&rules->death_mutex);
	dead = rules->someone_died;
	pthread_mutex_unlock(&rules->death_mutex);
	return (dead);
}

void	set_someone_died(t_rules *rules)
{
	pthread_mutex_lock(&rules->death_mutex);
	rules->someone_died = 1;
	pthread_mutex_unlock(&rules->death_mutex);
}

void	control_someone_died(t_rules *rules, t_philo *philos, int position)
{
	set_someone_died(rules);
	pthread_mutex_lock(&rules->print_mutex);
	printf("%ld %d died\n",
		get_time_in_ms() - rules->start_time,
		philos[position].id);
	pthread_mutex_unlock(&rules->print_mutex);
}

int	life(t_rules rules, t_philo *philos)
{
	int			i;
	pthread_t	monitor_thread;

	i = 0;
	while (i < rules.philo_count)
	{
		if (pthread_create(&philos[i].thread, NULL,
				philo_routine, &philos[i]) != 0)
			return (print_error("Fallo al crear thread"), 0);
		i++;
	}
	if (pthread_create(&monitor_thread, NULL, monitor_routine, philos) != 0)
		return (print_error("Fallo al crear monitor"), 0);
	i = 0;
	while (i < rules.philo_count)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
	pthread_join(monitor_thread, NULL);
	return (1);
}
