/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_setup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstaali <mstaali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 13:53:44 by mstaali           #+#    #+#             */
/*   Updated: 2024/08/05 13:21:09 by mstaali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	comapre_meals_eaten(t_philo *philos)
{
	t_args	*args;
	int		i;
	int		count;

	args = philos->args;
	i = -1;
	count = 0;
	while (++i < args->nbr_of_philos)
	{
		pthread_mutex_lock(&args->lock);
		if (philos[i].meal_counter >= args->nbr_of_meals_to_eat)
			count++;
		pthread_mutex_unlock(&args->lock);
	}
	if (count == args->nbr_of_philos)
		return (1);
	return (0);
}

static void	check_death(t_philo *philos)
{
	int		i;
	t_args	*args;

	args = philos->args;
	while (1)
	{
		i = -1;
		while (++i < args->nbr_of_philos)
		{
			pthread_mutex_lock(&args->lock);
			if (get_curr_time() - philos[i].last_meal >= args->time_to_die)
				return (print_message(philos + i, DIED, 1));
			pthread_mutex_unlock(&args->lock);
		}
		if (args->nbr_of_meals_to_eat > -1 && comapre_meals_eaten(philos))
			break ;
	}
}

int	thread_setup(t_philo *philos, t_args *args)
{
	int	i;

	args->starting_time = get_curr_time();
	i = -1;
	while (++i < args->nbr_of_philos)
		philos[i].last_meal = get_curr_time();
	i = -1;
	while (++i < args->nbr_of_philos)
	{
		if (pthread_create(&philos[i].thread, NULL,
				routine, (void *)(philos + i)))
			return (extern_error(1), 0);
		usleep(50);
	}
	i = -1;
	while (++i < args->nbr_of_philos)
		if (pthread_detach(philos[i].thread))
			return (extern_error(2), 0);
	check_death(philos);
	return (1);
}
