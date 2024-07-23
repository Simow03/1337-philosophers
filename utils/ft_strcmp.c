/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstaali <mstaali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 20:14:16 by mstaali           #+#    #+#             */
/*   Updated: 2024/07/23 20:14:17 by mstaali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo/philo.h"
#include "../philo_bonus/philo_bonus.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	if (!s1 || !s2)
	{
		if (s1 == NULL && s2 == NULL)
			return (0);
		else
			return (-1);
	}
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}
