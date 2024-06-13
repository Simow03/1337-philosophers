/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstaali <mstaali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 18:12:47 by mstaali           #+#    #+#             */
/*   Updated: 2024/06/13 13:00:06 by mstaali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"


int	init_data(t_args *args)
{
	args->philos = malloc(sizeof(t_philo) * args->nbr_of_philos);
	args->forks = malloc(sizeof(pthread_mutex_t) * args->nbr_of_philos);
	args->thread_id = malloc(sizeof(pthread_t) * args->nbr_of_philos);
	if (!args->philos || !args->thread_id || !args->forks)
		return (extern_error(0), 0);
	init_forks(args);
	init_philos(args);
	return (1);
}

void	init_forks(t_args *args)
{
	int	i;

	i = -1;
	while (++i < args->nbr_of_philos)
		pthread_mutex_init(&args->forks[i], NULL);
	args->philos[0].left_fork = &args->forks[0];
	args->philos[0].right_fork = &args->forks[args->nbr_of_philos - 1];
	i = 0;
	while (++i < args->nbr_of_philos)
	{
		args->philos[i].left_fork = &args->forks[i];
		args->philos[i].right_fork = &args->forks[i - 1];
	}
}

void	init_philos(t_args *args)
{
	int i;

	i = -1;
	while(++i < args->nbr_of_philos)
	{
		args->philos[i].args = args;
		args->philos[i].philo_id = i + 1;
		args->philos[i].meal_time = args->time_to_die;
		args->philos[i].is_eating = 0;
		args->philos[i].is_dead = 0;
		pthread_mutex_init(&args->philos[i].lock, NULL);
	}
}