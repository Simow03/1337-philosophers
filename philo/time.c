/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstaali <mstaali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 20:14:21 by mstaali           #+#    #+#             */
/*   Updated: 2024/09/09 12:06:21 by mstaali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		usleep(50);
	return (0);
}
