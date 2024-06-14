/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstaali <mstaali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 15:38:40 by mstaali           #+#    #+#             */
/*   Updated: 2024/06/14 18:15:17 by mstaali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <sys/time.h>

#define UNDERLINE "\033[4m"
#define BOLD "\033[1m"
#define RED "\033[31m"
#define DFLT "\033[0m"

# define TAKEN_FORK "has taken a fork"
# define THINKING "is thinking"
# define SLEEPING "is sleeping"
# define EATING "is eating"
# define DIED "died"

typedef struct s_philo t_philo;
typedef struct s_args t_args;


//-------------------- STRUCTS --------------------//
typedef struct s_args
{
	pthread_t		thread_id;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	lock;
	pthread_mutex_t	write;
	int				is_finished;
	int				nbr_of_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				nbr_of_meals_to_eat;
	long			current_time;
}	t_args;

typedef struct s_philo
{
	t_args			*args;
	pthread_t		thread;
	int				philo_id;
	long			meal_time;
	long			time_to_die;
	int				is_eating;
	int				meal_counter;
	int				is_dead;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	lock;
}	t_philo;

//-------------------- INITS --------------------//
int			init_data(t_args *args);
void		init_forks(t_args *args);
void		init_philos(t_args *args);



//-------------------- ROUTINE --------------------//
int			thread_setup(t_args *args);
long		get_curr_time(void);


//-------------------- UTILS --------------------//
long int	ft_atol(const char *str);
int			ft_isdigit(int c);
int			ft_iswhitespace(int c);
void		args_error(void);
void		nbr_error(const char *str, int flag);
void		neg_nbr_error(const char *str);
void		extern_error(int flag);