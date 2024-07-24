/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_setup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstaali <mstaali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 11:59:48 by mstaali           #+#    #+#             */
/*   Updated: 2024/07/24 12:53:38 by mstaali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	kill_process(t_b_philo *philos, t_b_args *args)
{
	int	i;

	i = -1;
	while (++i < args->nbr_of_philos)
		kill(philos[i].pid, SIGKILL);
	sem_unlink("forks");
	sem_unlink("write");
	sem_unlink("lock");
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
		if (args->nbr_of_meals_to_eat > -1 && philos->meal_counter > args->nbr_of_meals_to_eat)
			break ;
		sem_post(args->lock);
	}
}

void	process_setup(t_b_philo *philos, t_b_args *args)
{
	int	i;

	args->starting_time = get_curr_time();
	i = -1;
	while (++i < args->nbr_of_philos)
	{
		philos[i].pid = fork();
		if (i % 2)
			usleep(50);
		if (!philos[i].pid)
		{
			philos->last_meal = get_curr_time();
			if (pthread_create(&philos->thread, NULL, routine, (void *)philos))
				return ;
			pthread_detach(philos->thread);
			check_death(philos);
			exit(0);
		}
	}
	waitpid(-1, NULL, 0);
}
