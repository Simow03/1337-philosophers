/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 15:13:22 by mstaali           #+#    #+#             */
/*   Updated: 2024/07/22 15:44:36 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo/philo.h"
#include "../philo_bonus/philo_bonus.h"

long	get_curr_time(void)
{
	struct timeval	curr_time;

	if (gettimeofday(&curr_time, NULL) != 0)
		return (extern_error(3), 0);
	return ((curr_time.tv_sec * 1000) + (curr_time.tv_usec / 1000));
}

int	ft_usleep(useconds_t time)
{
	u_int64_t	start;

	start = get_curr_time();
	while ((get_curr_time() - start) < time)
		usleep(time / 10);
	return (0);
}
