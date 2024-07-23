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

static void get_args(t_args *args, char **av)
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

int	main(int ac, char **av)
{
	t_args	*args;
	t_philo	*philos;

    (void)philos;
	if (ac == 5 || ac == 6)
	{
		args = (t_args *)malloc(sizeof(t_args));
		if (!args)
			return (extern_error(0), EXIT_FAILURE);
		get_args(args, av);
	}
	else
		return (args_error(), EXIT_FAILURE);
}
