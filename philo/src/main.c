/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 11:42:52 by gojeda            #+#    #+#             */
/*   Updated: 2025/08/05 17:58:33 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int argc, char **argv)
{
	t_rules	rules;
	t_philo	*philos;
	int		i;

	if (!parse_args(argc, argv, &rules))
		return (1);
	if (!init_mutexes(&rules))
		return (1);
	philos = init_philos(&rules);
	if (!philos)
		return (print_error("Fallo al inicializar filosofos"), 1);
	if (!life(rules, philos))
		return (1);
	free(philos);
	free(rules.forks);
	i = 0;
	while (i < rules.philo_count)
		pthread_mutex_destroy(&rules.forks[i++]);
	pthread_mutex_destroy(&rules.print_mutex);
	pthread_mutex_destroy(&rules.death_mutex);
	return (0);
}
