/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 11:42:52 by gojeda            #+#    #+#             */
/*   Updated: 2025/08/04 17:55:46 by gojeda           ###   ########.fr       */
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
	i = 0;
	while (i < rules.philo_count)
	{
		if (pthread_create(&philos[i].thread, NULL,
				philo_routine, &philos[i]) != 0)
			return (print_error("Fallo al crear thread"), 1);
	}
	i = 0;
	while (i < rules.philo_count)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
	free(philos);
	free(rules.forks);
	return (0);
}
