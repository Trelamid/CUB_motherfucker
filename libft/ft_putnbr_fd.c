/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdakota <kdakota@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 14:20:47 by kdakota           #+#    #+#             */
/*   Updated: 2021/10/11 15:34:34 by kdakota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

int	ft_size_n(int n)
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

long int	ft_govnopower(int power, int num)
{
	long int	i;

	i = 1;
	while (power != 0)
	{
		i = i * num;
		power--;
	}
	return (i);
}

void	ft_putnbr_fd(int n, int fd)
{
	int	i;

	if (n == -2147483648)
		ft_putstr_fd("-2147483648", fd);
	else if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n = n * -1;
	}
	i = ft_size_n(n);
	while (i >= 0 && n >= 0)
	{
		ft_putchar_fd((((n / (ft_govnopower(i, 10))) % 10 ) + '0'), fd);
		i--;
	}
}
