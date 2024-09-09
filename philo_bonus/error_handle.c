/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstaali <mstaali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 20:13:55 by mstaali           #+#    #+#             */
/*   Updated: 2024/09/09 12:05:55 by mstaali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	args_error(void)
{
	printf("\n%s%s%serror:%s%s invalid arguments!\n\n\t%susage:%s \
	./philo [nbr_of_philos] [time_to_die] [time_to_eat] [time_to_sleep] [nbr_of_meals_to_eat]\n\t%s%snote:%s  \"nbr_of_meals_to_eat\" is optional.\
	\n\n", BOLD, UNDERLINE, RED, DFLT, BOLD, UNDERLINE, DFLT, BOLD, \
	UNDERLINE, DFLT);
}

void	nbr_error(const char *str, int flag)
{
	if (flag == 0)
		printf("\n%s%s%serror:%s%s invalid input!\n\n\t\"%s\":"
			"%s is not a valid number.\n\n", BOLD, UNDERLINE, RED,
			DFLT, BOLD, str, DFLT);
	else if (flag == 1)
		printf("\n%s%s%serror:%s%s invalid input!\n\n\t\"%s\":%s"
			" number is too big.\n\n", BOLD, UNDERLINE, RED, DFLT,
			BOLD, str, DFLT);
}

void	neg_nbr_error(const char *str)
{
	printf("\n%s%s%serror:%s%s invalid input!\n\n\t\"%s\":%s negative"
		" numbers are not allowed.\n\n", BOLD, UNDERLINE,
		RED, DFLT, BOLD, str, DFLT);
}

void	extern_error(int flag)
{
	if (flag == 0)
		printf("\n%s%s%serror:%s%s Failed to allocate memory.\n\n",
			BOLD, UNDERLINE, RED, DFLT, BOLD);
	else if (flag == 1)
		printf("\n%s%s%serror:%s%s Failed to create thread.\n\n",
			BOLD, UNDERLINE, RED, DFLT, BOLD);
	else if (flag == 2)
		printf("\n%s%s%serror:%s%s Failed to detach thread.\n\n",
			BOLD, UNDERLINE, RED, DFLT, BOLD);
	else if (flag == 3)
		printf("\n%s%s%serror:%s%s Failed to \'gettimeofday()\'.\n\n",
			BOLD, UNDERLINE, RED, DFLT, BOLD);
}
