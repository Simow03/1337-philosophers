/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstaali <mstaali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 13:53:44 by mstaali           #+#    #+#             */
/*   Updated: 2024/06/28 15:55:45 by mstaali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*single_routine(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *)philo_ptr;
	while (philo->args->is_dead == 0)
	{
		pthread_mutex_lock(&philo->lock);
		if (get_curr_time() >= philo->time_to_die && philo->is_eating == 0)
			print_message(philo, DIED);
		if (philo->meal_counter == philo->args->nbr_of_meals_to_eat)
		{
			pthread_mutex_lock(&philo->args->lock);
			philo->args->is_finished++;
			philo->meal_counter++;
			pthread_mutex_unlock(&philo->args->lock);
		}
		pthread_mutex_unlock(&philo->lock);
	}
	return ((void *)0);
}

void	*global_routine(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *)philo_ptr;
	philo->time_to_die = philo->args->time_to_die + get_curr_time();
	if (pthread_create(&philo->thread, NULL, &single_routine, (void *)philo))
		return (extern_error(1), (void *)0);
	while (philo->args->is_dead == 0)
	{
		eating_process(philo);
		print_message(philo, THINKING);
	}
	if (pthread_join(philo->thread, NULL) != 0)
		return (extern_error(3), (void *)0);
	return ((void *)1);
}

int	handle_one_philo(t_args *args)
{
	args->starting_time = get_curr_time();
	if (pthread_create(&args->thread_id[0], NULL,
			&global_routine, &args->philos[0]))
		return (extern_error(1), 0);
	pthread_detach(args->thread_id[0]);
	while (args->is_dead == 0)
		ft_usleep(0);
	cleanup(args);
	return (1);
}

int	thread_setup(t_args *args)
{
	int			i;
	pthread_t	t1;

	i = -1;
	if (args->nbr_of_philos == 1)
		return (handle_one_philo(args));
	else
	{
		args->starting_time = get_curr_time();
		if (args->nbr_of_meals_to_eat > 0)
			if (pthread_create(&t1, NULL, &meals_eaten, &args->philos[0]))
				return (extern_error(1), 0);
		while (++i < args->nbr_of_philos)
		{
			if (pthread_create(&args->thread_id[i], NULL,
					&global_routine, &args->philos[i]))
				return (extern_error(1), 0);
			ft_usleep(1);
		}
		i = -1;
		while (++i < args->nbr_of_philos)
			if (pthread_join(args->thread_id[i], NULL) != 0)
				return (extern_error(3), 0);
	}
	return (cleanup(args), 1);
}
