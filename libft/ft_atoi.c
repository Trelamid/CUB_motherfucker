/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdakota <kdakota@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 14:20:47 by kdakota           #+#    #+#             */
/*   Updated: 2021/10/07 14:20:47 by kdakota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_isspace(char str)
{
	if (str == '\t' || str == '\r' || str == '\v' || str == '\n' || str == '\f'
		|| str == ' ')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	unsigned long int	i;
	long int			rez;
	long int			sign;

	i = 0;
	sign = 1;
	rez = 0;
	while (ft_isspace(str[i]) == 1)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (rez * sign * 10 > 21474836470)
			return (-1);
		if (rez * 10 * sign < -21474836480)
			return (0);
		rez = rez * 10 + (str[i] - '0');
		i++;
	}
	return ((int)(rez * sign));
}
