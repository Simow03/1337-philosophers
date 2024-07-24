/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstaali <mstaali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 20:13:45 by mstaali           #+#    #+#             */
/*   Updated: 2024/07/23 20:13:45 by mstaali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>

# define UNDERLINE "\033[4m"
# define BOLD "\033[1m"
# define RED "\033[31m"
# define DFLT "\033[0m"

# define TAKEN_FORK "has taken a fork"
# define THINKING "is thinking"
# define SLEEPING "is sleeping"
# define EATING "is eating"
# define DIED "died"

//-------------------- STRUCTS --------------------//

typedef struct s_b_args
{
	sem_t			*forks;
	sem_t			*lock;
	sem_t			*write;
	int				nbr_of_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				nbr_of_meals_to_eat;
	long			starting_time;
}	t_b_args;

typedef struct s_b_philo
{
	struct s_b_args	*args;
	pthread_t		thread;
	int				philo_id;
	int				meal_counter;
	long			last_meal;
	pid_t			pid;
}	t_b_philo;

//-------------------- ROUTINE --------------------//
void		process_setup(t_b_philo *philos, t_b_args *args);
void		kill_process(t_b_philo *philos, t_b_args *args);
void		*routine(void *philo_ptr);
void		eating_process_bonus(t_b_philo *philo);
void		print_message_bonus(t_b_philo *philo, char *flag, int unlock);

//-------------------- UTILS --------------------//
long int	ft_atol(const char *str);
int			ft_isdigit(int c);
long		get_curr_time(void);
int			ft_usleep(useconds_t time);
int			ft_iswhitespace(int c);
int			ft_strcmp(const char *s1, const char *s2);
void		args_error(void);
void		nbr_error(const char *str, int flag);
void		neg_nbr_error(const char *str);
void		extern_error(int flag);

#endif