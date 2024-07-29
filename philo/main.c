/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstaali <mstaali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 20:13:11 by mstaali           #+#    #+#             */
/*   Updated: 2024/07/29 13:09:35 by mstaali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	get_args(t_args *args, char **av)
{
	args->nbr_of_philos = (int)ft_atol(av[1]);
	if (args->nbr_of_philos <= 0)
		return (0);
	args->time_to_die = ft_atol(av[2]);
	if (args->time_to_die == -1)
		return (0);
	args->time_to_eat = ft_atol(av[3]);
	if (args->time_to_eat == -1)
		return (0);
	args->time_to_sleep = ft_atol(av[4]);
	if (args->time_to_sleep == -1)
		return (0);
	if (av[5])
	{
		args->nbr_of_meals_to_eat = (int)ft_atol(av[5]);
		if (args->nbr_of_meals_to_eat == -1)
			return (0);
	}
	else
		args->nbr_of_meals_to_eat = -2;
	return (1);
}

static int	init_data(t_args *args)
{
	int	i;

	args->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* args->nbr_of_philos);
	if (!args->forks)
		return (extern_error(0), 0);
	i = -1;
	while (++i < args->nbr_of_philos)
		pthread_mutex_init(&args->forks[i], NULL);
	pthread_mutex_init(&args->write, NULL);
	pthread_mutex_init(&args->lock, NULL);
	return (1);
}

static t_philo	*init_philos(t_args *args)
{
	t_philo	*philos;
	int		i;

	philos = (t_philo *)malloc(sizeof(t_philo) * args->nbr_of_philos);
	if (!philos)
		return (extern_error(0), NULL);
	i = -1;
	while (++i < args->nbr_of_philos)
	{
		philos[i].philo_id = i;
		philos[i].args = args;
		philos[i].meal_counter = 0;
	}
	return (philos);
}

int	main(int ac, char **av)
{
	t_args	*args;
	t_philo	*philos;

	if (ac == 5 || ac == 6)
	{
		args = (t_args *)malloc(sizeof(t_args));
		if (!args)
			return (extern_error(0), EXIT_FAILURE);
		if (!get_args(args, av))
			return (free(args), EXIT_FAILURE);
		if (!init_data(args))
			return (free(args), EXIT_FAILURE);
		philos = init_philos(args);
		if (!philos)
			return (free(args->forks), free(args), EXIT_FAILURE);
		if (!thread_setup(philos, args))
			return (free(args->forks), free(args), free(philos), EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
	else
		return (args_error(), EXIT_FAILURE);
}
