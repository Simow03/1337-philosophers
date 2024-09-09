/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstaali <mstaali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 12:07:40 by mstaali           #+#    #+#             */
/*   Updated: 2024/09/09 12:09:04 by mstaali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long int	ft_atol(const char *str)
{
	long	result;
	int		i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] && ft_iswhitespace(str[i]))
		i++;
	if (str[i] == '+')
		i++;
	if (str[i] == '-')
		return (neg_nbr_error(str), -1);
	result = 0;
	if (!ft_isdigit(str[i]))
		return (nbr_error(str, 0), -1);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (nbr_error(str, 0), -1);
		result = result * 10 + (str[i] - '0');
		if (result > INT_MAX)
			return (nbr_error(str, 1), -1);
		i++;
	}
	return (result);
}

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

int	ft_iswhitespace(int c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r'
		|| c == '\v' || c == '\f');
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
