/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstaali <mstaali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 15:38:40 by mstaali           #+#    #+#             */
/*   Updated: 2024/06/28 15:57:24 by mstaali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <sys/time.h>

# define UNDERLINE "\033[4m"
# define BOLD "\033[1m"
# define RED "\033[31m"
# define DFLT "\033[0m"

# define TAKEN_FORK "has taken a fork"
# define THINKING "is thinking"
# define SLEEPING "is sleeping"
# define EATING "is eating"
# define DIED "died"

typedef struct s_philo	t_philo;
typedef struct s_args	t_args;

//-------------------- STRUCTS --------------------//
typedef struct s_args
{
	pthread_t		*thread_id;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	lock;
	pthread_mutex_t	write;
	int				is_finished;
	int				is_dead;
	int				nbr_of_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				nbr_of_meals_to_eat;
	long			starting_time;
}	t_args;

typedef struct s_philo
{
	struct s_args	*args;
	pthread_t		thread;
	int				philo_id;
	int				meal_counter;
	int				is_eating;
	int				status;
	long			time_to_die;
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
int			ft_usleep(useconds_t time);
void		*meals_eaten(void	*philo_ptr);
void		eating_process(t_philo *philo);
void		print_message(t_philo *philo, char *flag);
void		cleanup(t_args *args);

//-------------------- UTILS --------------------//
long int	ft_atol(const char *str);
int			ft_isdigit(int c);
int			ft_iswhitespace(int c);
int			ft_strcmp(const char *s1, const char *s2);
void		args_error(void);
void		nbr_error(const char *str, int flag);
void		neg_nbr_error(const char *str);
void		extern_error(int flag);

#endif