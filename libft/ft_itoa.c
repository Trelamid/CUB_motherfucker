/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdakota <kdakota@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 14:21:04 by kdakota           #+#    #+#             */
/*   Updated: 2021/10/08 14:31:54 by kdakota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stdlib.h>

char	*ft_for_itoa(char *str, int n, int i)
{
	str = malloc(i);
	if (str == NULL)
		return (NULL);
	str = ft_memset(str, '0', i);
	str[i - 1] = '\0';
	while (n >= 10)
	{
		str[i - 2] = (n % 10) + '0';
		n = n / 10;
		i--;
	}
	str[i - 2] = n + '0';
	return (str);
}

int	ft_size_s(int n)
{
	int	s;

	s = 0;
	if (n == -2147483648)
	{
		n = -214748364;
		s += 1;
	}
	while (n >= 10 || n * -1 >= 10)
	{
		n = n / 10;
		s++;
	}
	return (s);
}

char	*ft_itoa(int num)
{
	int			s;
	char		*str;

	str = NULL;
	s = ft_size_s(num) + 2;
	if (num >= 0)
		str = ft_for_itoa(str, num, s);
	else if (num == -2147483648)
		str = ft_for_itoa(str, (147483648), (s + 1));
	else
		str = ft_for_itoa(str, (num * -1), (s + 1));
	if (str == NULL)
		return (NULL);
	if (num == -2147483648)
		str[1] = '2';
	if (num < 0)
		str[0] = '-';
	return (str);
}
