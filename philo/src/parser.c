/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 11:46:35 by gojeda            #+#    #+#             */
/*   Updated: 2025/08/04 17:01:25 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	is_all_digits(char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	parse_args(int argc, char **argv, t_rules *rules)
{
	int	i;

	if (argc != 5 && argc != 6)
		return (print_error("Número inválido de argumentos"), 0);
	i = 1;
	while (i < argc)
	{
		if (!is_all_digits(argv[i]))
			return (print_error("Todos los argumentos deben ser números"), 0);
		i++;
	}
	rules->philo_count = ft_atoi(argv[1]);
	rules->time_to_die = ft_atoi(argv[2]);
	rules->time_to_eat = ft_atoi(argv[3]);
	rules->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		rules->must_eat_count = ft_atoi(argv[5]);
	else
		rules->must_eat_count = -1;
	rules->someone_died = 0;
	rules->start_time = get_time_in_ms();
	return (1);
}
