/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstaali <mstaali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 15:38:40 by mstaali           #+#    #+#             */
/*   Updated: 2024/06/10 18:16:01 by mstaali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <time.h>

typedef struct s_fork
{
	pthread_mutex_t	fork;
	int				fork_id;
}	t_fork;

typedef struct s_args
{
	int		nbr_of_philos;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	int		nbr_of_meals_to_eat;
}	t_args;

typedef struct s_philo
{
	int			philo_id;
	int			meals_nbr;
	long		meal_time;
	int			is_eating;
	int			is_sleeping;
	int			is_thinking;
	int			is_dead;
	t_fork		*left_fork;
	t_fork		*right_fork;
	pthread_t	thread;
	t_args		*args;
}	t_philo;
