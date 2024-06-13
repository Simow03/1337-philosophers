/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstaali <mstaali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 13:53:44 by mstaali           #+#    #+#             */
/*   Updated: 2024/06/13 17:27:03 by mstaali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*single_routine(void *philo)
{
}

void	*global_routine(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *)philo_ptr;
	philo->time_to_die = philo->args->time_to_die + get_curr_time();
	if (pthread_create(&philo->thread, NULL, &single_routine, (void *)philo) != 0)
		return (extern_error(1), 0);
	while (philo->is_dead == 0)
	{
		//eat and think
	}
	if (pthread_join(philo->thread, NULL) != 0)
		return (extern_error(3), 0);
	return (1);
}


void	cleanup(t_args *args)
{
	int	i;

	i = -1;
	while (++i < args->nbr_of_philos)
	{
		pthread_mutex_destroy(&args->forks[i]);
		pthread_mutex_destroy(&args->philos[i].lock);
	}
	free(args->thread_id);
	free(args->forks);
	free(args->philos);
}

int	handle_one_philo(t_args *args)
{
	if (pthread_create(&args->thread_id[0], NULL, &global_routine, &args->philos[0]) != 0)
		return (extern_error(1), 0);
	if (pthread_detach(&args->thread_id[0]) != 0);
		return (extern_error(2), 0);
	while (args->philos[0].is_dead == 0)
		usleep(0);
	cleanup(args);
	return (1);
}

int	thread_setup(t_args *args)
{
	args->current_time = get_curr_time();
	if (args->nbr_of_philos == 1)
		if(!handle_one_philo(args))
			return (0);
	else
	{
	}
	cleanup(args);
	return (1);
}
