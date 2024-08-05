/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstaali <mstaali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 15:52:35 by mstaali           #+#    #+#             */
/*   Updated: 2024/08/05 12:54:05 by mstaali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_message_bonus(t_b_philo *philo, char *flag, int unlock)
{
	t_b_args	*args;
	long		curr_time;

	args = philo->args;
	sem_wait(args->write);
	curr_time = get_curr_time() - args->starting_time;
	if (ft_strcmp(flag, DIED) == 0)
		printf("%ld  %d %s%s%s\n", curr_time, philo->philo_id + 1,
			RED, flag, DFLT);
	else
		printf("%ld  %d %s\n", curr_time, philo->philo_id + 1, flag);
	if (!unlock)
		sem_post(args->write);
}

void	eating_process_bonus(t_b_philo *philo)
{
	t_b_args	*args;

	args = philo->args;
	sem_wait(args->forks);
	print_message_bonus(philo, TAKEN_FORK, 0);
	sem_wait(args->forks);
	print_message_bonus(philo, TAKEN_FORK, 0);
	print_message_bonus(philo, EATING, 0);
	ft_usleep(args->time_to_eat);
	sem_post(args->forks);
	sem_post(args->forks);
	sem_wait(args->lock);
	philo->meal_counter++;
	philo->last_meal = get_curr_time();
	sem_post(args->lock);
}

void	*routine(void *philo_ptr)
{
	t_b_philo	*philo;

	philo = (t_b_philo *)philo_ptr;
	while (1)
	{
		eating_process_bonus(philo);
		print_message_bonus(philo, SLEEPING, 0);
		ft_usleep(philo->args->time_to_sleep);
		print_message_bonus(philo, THINKING, 0);
	}
	return ((void *)0);
}
