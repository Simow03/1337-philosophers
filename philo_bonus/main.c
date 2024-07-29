/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstaali <mstaali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 20:13:27 by mstaali           #+#    #+#             */
/*   Updated: 2024/07/23 20:13:27 by mstaali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	get_args(t_b_args *args, char **av)
{
	args->nbr_of_philos = (int)ft_atol(av[1]);
	if (args->nbr_of_philos <= 0)
		exit(EXIT_FAILURE);
	args->time_to_die = ft_atol(av[2]);
	if (args->time_to_die == -1)
		exit(EXIT_FAILURE);
	args->time_to_eat = ft_atol(av[3]);
	if (args->time_to_eat == -1)
		exit(EXIT_FAILURE);
	args->time_to_sleep = ft_atol(av[4]);
	if (args->time_to_sleep == -1)
		exit(EXIT_FAILURE);
	if (av[5])
	{
		args->nbr_of_meals_to_eat = (int)ft_atol(av[5]);
		if (args->nbr_of_meals_to_eat == -1)
			exit(EXIT_FAILURE);
	}
	else
		args->nbr_of_meals_to_eat = -2;
}

static void	init_data(t_b_args *args)
{
	sem_unlink("/forks");
	sem_unlink("/write");
	sem_unlink("/lock");
	args->forks = sem_open("/forks", O_CREAT, 0600, args->nbr_of_philos);
	args->write = sem_open("/write", O_CREAT, 0600, 1);
	args->lock = sem_open("/lock", O_CREAT, 0600, 1);
}

static t_b_philo	*init_philos(t_b_args *args)
{
	int			i;
	t_b_philo	*philos;

	philos = (t_b_philo *)malloc(sizeof(t_b_philo) * args->nbr_of_philos);
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

void f()
{
	system("leaks philo_bonus");
}

int	main(int ac, char **av)
{
	t_b_args	*args;
	t_b_philo	*philos;

	atexit(f);
	if (ac == 5 || ac == 6)
	{
		args = (t_b_args *)malloc(sizeof(t_b_args));
		if (!args)
			return (extern_error(0), EXIT_FAILURE);
		get_args(args, av);
		init_data(args);
		philos = init_philos(args);
		if (!philos)
			exit(EXIT_FAILURE);
		args->starting_time = get_curr_time();
		process_setup(philos, args);
		kill_process(philos, args);
		free(args);
		free(philos);
	}
	else
		return (args_error(), EXIT_FAILURE);
}
