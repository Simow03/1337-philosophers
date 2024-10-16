/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_setup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstaali <mstaali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 11:59:48 by mstaali           #+#    #+#             */
/*   Updated: 2024/10/12 17:41:10 by mstaali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	kill_process(t_b_philo *philos, t_b_args *args)
{
	int	i;

	i = -1;
	while (++i < args->nbr_of_philos)
		kill(philos[i].pid, SIGKILL);
	sem_unlink("/forks");
	sem_unlink("/write");
	sem_unlink("/lock");
	sem_close(args->forks);
	sem_close(args->write);
	sem_close(args->lock);
}

static void	check_death(t_b_philo *philos)
{
	t_b_args	*args;

	args = philos->args;
	while (1)
	{
		sem_wait(args->lock);
		if (get_curr_time() - philos->last_meal >= args->time_to_die)
			return (print_message_bonus(philos, DIED, 1));
		if (args->nbr_of_meals_to_eat > -1
			&& philos->meal_counter > args->nbr_of_meals_to_eat)
			break ;
		sem_post(args->lock);
	}
}

void	process_setup(t_b_philo *philos, t_b_args *args)
{
	int	i;

	i = -1;
	while (++i < args->nbr_of_philos)
	{
		philos[i].pid = fork();
		if (!philos[i].pid)
		{
			philos[i].last_meal = get_curr_time();
			if (pthread_create(&philos[i].thread,
					NULL, routine, (void *)(philos + i)))
				return (extern_error(1));
			if (pthread_detach(philos[i].thread))
				return (extern_error(2));
			check_death(&philos[i]);
			exit(EXIT_SUCCESS);
		}
		usleep(50);
	}
	waitpid(-1, NULL, 0);
}
