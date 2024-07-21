/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstaali <mstaali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 13:53:44 by mstaali           #+#    #+#             */
/*   Updated: 2024/07/21 18:48:24 by mstaali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void	*philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *)philo_ptr;
	while (1)
	{
		eating_process(philo);
		print_message(philo, SLEEPING, 0);
		ft_usleep(philo->args->time_to_sleep);
		print_message(philo, THINKING, 0);
	}
	return ((void *)0);
}

int	check_meals(t_philo *philos)
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

void	check_death(t_philo *philos)
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
		if (args->nbr_of_meals_to_eat > -1 && check_meals(philos))
			break;
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
		if (i % 2)
			usleep(50);
		if (pthread_create(&philos[i].thread, NULL, routine, (void *)(philos + i)))
			return (extern_error(1), 0);
	}
	i = -1;
	while (++i < args->nbr_of_philos)
		pthread_detach(philos[i].thread);
	check_death(philos);
	return (1);
}
