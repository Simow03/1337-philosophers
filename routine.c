/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstaali <mstaali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 13:53:44 by mstaali           #+#    #+#             */
/*   Updated: 2024/06/27 20:18:40 by mstaali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_message(t_philo *philo, char *flag)
{
	long	curr_time;

	pthread_mutex_lock(&philo->args->write);
	curr_time = get_curr_time() - philo->args->starting_time;
	if (ft_strcmp(flag, DIED) == 0 && philo->args->is_dead == 0)
	{
		printf("%ld  %d %s%s\n", curr_time, philo->philo_id, RED, flag);
		philo->args->is_dead = 1;
	}
	if (!philo->args->is_dead)
		printf("%ld  %d %s\n", curr_time, philo->philo_id, flag);
	pthread_mutex_unlock(&philo->args->write);
}

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

void	*global_routine(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *)philo_ptr;
	philo->time_to_die = philo->args->time_to_die + get_curr_time();
	if (pthread_create(&philo->thread, NULL, &single_routine, (void *)philo) != 0)
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
	args->starting_time = get_curr_time();
	if (pthread_create(&args->thread_id[0], NULL, &global_routine, &args->philos[0]) != 0)
		return (extern_error(1), 0);
	pthread_detach(args->thread_id[0]);
	while (args->is_dead == 0)
		ft_usleep(0);
	cleanup(args);
	return (1);
}

void	*meals_eaten(void	*philo_ptr)
{
	t_philo    *philo;

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

int	thread_setup(t_args *args)
{
	int			i;
	pthread_t	t1;

	i = -1;
	if (args->nbr_of_philos == 1)
		return(handle_one_philo(args));
	else
	{
		args->starting_time = get_curr_time();
		if (args->nbr_of_meals_to_eat > 0)
			if (pthread_create(&t1, NULL, &meals_eaten, &args->philos[0]))
				return (extern_error(1), 0);
		while (++i < args->nbr_of_philos)
		{
			if (pthread_create(&args->thread_id[i], NULL, &global_routine, &args->philos[i]) != 0)
				return (extern_error(1), 0);
			ft_usleep(1);
		}
		i = -1;
		while (++i < args->nbr_of_philos)
			if (pthread_join(args->thread_id[i], NULL) != 0)
				return (extern_error(3), 0);
	}
	cleanup(args);
	return (1);
}
