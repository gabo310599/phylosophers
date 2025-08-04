/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 11:27:00 by gojeda            #+#    #+#             */
/*   Updated: 2025/07/31 11:55:03 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>

/* ************************************************************************** */
//STRUCTURES

//Rules
typedef struct s_rules
{
	int				philo_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_count;
	int				someone_died;
	long			start_time;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	*forks;
}	t_rules;

//Philos
typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long			last_meal;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_rules			*rules;
}	t_philo;
/* ************************************************************************** */

/* ************************************************************************** */
//FUNCTIONS

size_t	ft_strlen(const char *str);
int		ft_atoi(const char *nptr);
void	print_error(char *msg);
/* ************************************************************************** */
#endif