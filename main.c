/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstaali <mstaali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 18:09:39 by mstaali           #+#    #+#             */
/*   Updated: 2024/06/27 20:07:50 by mstaali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	get_args(t_args *args, char **av)
{
	args->nbr_of_philos = (int)ft_atol(av[1]);
	args->time_to_die = ft_atol(av[2]);
	args->time_to_eat = ft_atol(av[3]);
	args->time_to_sleep = ft_atol(av[4]);
	if (av[5])
		args->nbr_of_meals_to_eat = (int)ft_atol(av[5]);
	else
		args->nbr_of_meals_to_eat = -2;
}

int is_valid_args(t_args *args)
{
	if (args->nbr_of_philos == -1 || args->nbr_of_philos == 0 || args->time_to_die == -1 || args->time_to_eat == -1 ||
		args->time_to_sleep == -1 || args->nbr_of_meals_to_eat == -1)
			return (0);
	return (1);
}

int	main(int ac, char **av)
{
	t_args	args;

	if (ac == 5 || ac == 6)
	{
		get_args(&args, av);
		if (!is_valid_args(&args))
			return (EXIT_FAILURE);
		if (!init_data(&args))
			return (EXIT_FAILURE);
		if (!thread_setup(&args))
			return (EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
	else
		return (args_error(), EXIT_FAILURE);
}
