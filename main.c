/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstaali <mstaali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 18:09:39 by mstaali           #+#    #+#             */
/*   Updated: 2024/06/11 21:08:36 by mstaali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	ft_iswhitespace(int c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r' 
		|| c == '\v' || c == '\f');
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

void	error_mssg(void)
{
	printf("\n%s%s%serror:%s%s invalid arguments!\n\n\t%susage:%s \
	./philo [nbr_of_philos] [time_to_die] [time_to_eat] [time_to_sleep] [nbr_of_meals_to_eat]\n\t%s%snote:%s  \"nbr_of_meals_to_eat\" is optional.\
	\n\n", BOLD, UNDERLINE, RED, DFLT, BOLD, UNDERLINE, DFLT, BOLD, \
	UNDERLINE, DFLT);
}

void	nbr_error(const char *str, int flag)
{
	if (flag == 0)
		printf("\n%s%s%serror:%s%s invalid input!\n\n\t\"%s\":%s is not a valid number.\n\n", BOLD, UNDERLINE, RED, DFLT, BOLD, str, DFLT);
	else if (flag == 1)
		printf("\n%s%s%serror:%s%s invalid input!\n\n\t\"%s\":%s number is too big.\n\n", BOLD, UNDERLINE, RED, DFLT, BOLD, str, DFLT);
}

void	neg_nbr_error(const char *str)
{
	printf("\n%s%s%serror:%s%s invalid input!\n\n\t\"%s\":%s negative numbers are not allowed.\n\n", BOLD, UNDERLINE, \
	RED, DFLT, BOLD, str, DFLT);
}

long int	ft_atol(const char *str)
{
	long	result;
	int		i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] && ft_iswhitespace(str[i]))
		i++;
	if (str[i] == '+')
		i++;
	if (str[i] == '-')
		return (neg_nbr_error(str), -1);
	result = 0;
	if (!ft_isdigit(str[i]))
		return (nbr_error(str, 0), -1);
	while (str[i] && ft_isdigit(str[i]))
	{
        result = result * 10 + (str[i] - '0');
		if (result > INT_MAX)
			return (nbr_error(str, 1), -1);
        i++;
	}
	return (result);
}

void	init_values(t_args *args, char **av)
{
	args->nbr_of_philos = (int)ft_atol(av[1]);
	args->time_to_die = ft_atol(av[2]);
	args->time_to_eat = ft_atol(av[3]);
	args->time_to_sleep = ft_atol(av[4]);
	if (av[5])
		args->nbr_of_meals_to_eat = (int)ft_atol(av[5]);
	else
		args->nbr_of_meals_to_eat = 0;
}

int is_valid_values(t_args *args)
{
	if (args->nbr_of_philos == -1 || args->time_to_die == -1 || args->time_to_eat == -1 ||
		args->time_to_sleep == -1 || args->nbr_of_meals_to_eat == -1)
			return (0);
	return (1);
}

int	main(int ac, char **av)
{
	t_args	args;

	if (ac == 5 || ac == 6)
	{
		init_values(&args, av);
		if (is_valid_values(&args) == 0)
			return (EXIT_FAILURE);
	}
	else
		error_mssg();
}
