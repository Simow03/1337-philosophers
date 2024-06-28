/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstaali <mstaali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 15:52:35 by mstaali           #+#    #+#             */
/*   Updated: 2024/06/28 15:55:52 by mstaali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	print_message(t_philo *philo, char *flag)
{
	long	curr_time;

	pthread_mutex_lock(&philo->args->write);
	curr_time = get_curr_time() - philo->args->starting_time;
	if (ft_strcmp(flag, DIED) == 0 && philo->args->is_dead == 0)
	{
		printf("%ld  %d %s%s%s\n", curr_time, philo->philo_id, RED, flag, DFLT);
		philo->args->is_dead = 1;
	}
	if (!philo->args->is_dead)
		printf("%ld  %d %s\n", curr_time, philo->philo_id, flag);
	pthread_mutex_unlock(&philo->args->write);
}

void	eating_process(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	print_message(philo, TAKEN_FORK);
	pthread_mutex_lock(philo->left_fork);
	print_message(philo, TAKEN_FORK);
	pthread_mutex_lock(&philo->lock);
	philo->is_eating = 1;
	philo->time_to_die = get_curr_time() + philo->args->time_to_die;
	print_message(philo, EATING);
	philo->meal_counter++;
	ft_usleep(philo->args->time_to_eat);
	philo->is_eating = 0;
	pthread_mutex_unlock(&philo->lock);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	print_message(philo, SLEEPING);
	ft_usleep(philo->args->time_to_sleep);
}

void	*meals_eaten(void	*philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *)philo_ptr;
	while (philo->args->is_dead == 0)
	{
		pthread_mutex_lock(&philo->lock);
		if (philo->args->is_finished >= philo->args->nbr_of_philos)
			philo->args->is_dead = 1;
		pthread_mutex_unlock(&philo->lock);
	}
	return ((void *)0);
}
