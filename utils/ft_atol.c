/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstaali <mstaali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 11:16:51 by mstaali           #+#    #+#             */
/*   Updated: 2024/06/28 14:22:59 by mstaali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

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
	while (str[i] && ft_isdigit(str[i]))
	{
		result = result * 10 + (str[i] - '0');
		if (result > INT_MAX)
			return (nbr_error(str, 1), -1);
		i++;
	}
	return (result);
}
