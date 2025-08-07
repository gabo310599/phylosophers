/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 11:42:52 by gojeda            #+#    #+#             */
/*   Updated: 2025/08/07 19:50:04 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int argc, char **argv)
{
	t_rules	rules;
	t_philo	*philos;

	if (!parse_args(argc, argv, &rules))
		return (1);
	if (!init_mutexes(&rules))
		return (1);
	rules.start_time = get_time_in_ms();
	philos = init_philos(&rules);
	if (!philos)
		return (print_error("Fallo al inicializar filosofos"), 1);
	if (!life(&rules, philos))
	{
		destroy_mutex(philos, rules.philo_count, &rules);
		return (1);
	}
	destroy_mutex(philos, rules.philo_count, &rules);
	return (0);
}
