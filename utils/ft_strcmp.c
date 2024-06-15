/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstaali <mstaali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 16:14:34 by mstaali           #+#    #+#             */
/*   Updated: 2024/06/15 16:23:35 by mstaali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"
#include <string.h>

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
			return *s1 - *s2;
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}
