/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstaali <mstaali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 15:52:35 by mstaali           #+#    #+#             */
/*   Updated: 2024/10/12 18:03:51 by mstaali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_message(t_philo *philo, char *flag, int unlock)
{
	long	curr_time;
	t_args	*args;

	args = philo->args;
	pthread_mutex_lock(&args->write);
	curr_time = get_curr_time() - args->starting_time;
	if (ft_strcmp(flag, DIED) == 0)
		printf("%ld  %d %s%s%s\n", curr_time, philo->philo_id + 1,
			RED, flag, DFLT);
	else
		printf("%ld  %d %s\n", curr_time, philo->philo_id + 1, flag);
	if (!unlock)
		pthread_mutex_unlock(&args->write);
}

void	eating_process(t_philo *philo)
{
	t_args	*args;
	size_t	l_fork_id;
	size_t	r_fork_id;

	args = philo->args;
	l_fork_id = philo->philo_id;
	r_fork_id = (philo->philo_id + 1) % args->nbr_of_philos;
	pthread_mutex_lock(&args->forks[l_fork_id]);
	print_message(philo, TAKEN_FORK, 0);
	pthread_mutex_lock(&args->forks[r_fork_id]);
	print_message(philo, TAKEN_FORK, 0);
	print_message(philo, EATING, 0);
	philo->last_meal = get_curr_time();
	ft_usleep(args->time_to_eat);
	pthread_mutex_unlock(&args->forks[l_fork_id]);
	pthread_mutex_unlock(&args->forks[r_fork_id]);
	pthread_mutex_lock(&args->lock);
	philo->meal_counter++;
	pthread_mutex_unlock(&args->lock);
}

void	*routine(void *philo_ptr)
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
