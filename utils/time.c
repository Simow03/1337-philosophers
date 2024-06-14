/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstaali <mstaali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 15:13:22 by mstaali           #+#    #+#             */
/*   Updated: 2024/06/13 15:27:43 by mstaali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

long	get_curr_time(void)
{
	struct timeval	curr_time;

	if (gettimeofday(&curr_time, NULL) != 0)
		return (extern_error(3), 0);
	return ((curr_time.tv_sec * 1000) + (curr_time.tv_usec / 1000));
}