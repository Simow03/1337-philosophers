/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstaali <mstaali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 18:09:39 by mstaali           #+#    #+#             */
/*   Updated: 2024/06/10 18:56:05 by mstaali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

# define UNDERLINE "\033[4m"
# define BOLD "\033[1m"
# define RED "\033[31m"
# define DFLT "\033[0m"

void	error_mssg(void)
{
	printf("\n%s%s%serror:%s%s invalid arguments!\n\n\t%susage:%s ./philo [nbr_of_philos] [time_to_die] [time_to_eat] [time_to_sleep] [nbr_of_meals_to_eat]\n\t%s%snote:%s \"nbr_of_meals_to_eat\" is optional.\n\n",BOLD, UNDERLINE, RED, DFLT, BOLD, UNDERLINE, DFLT, BOLD, UNDERLINE, DFLT);
}
int	main(int ac, char **av)
{
	(void)av;
	if (ac == 5 || ac == 6)
	{
		//work
	}
	else
		error_mssg();
}