/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdakota <kdakota@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 14:20:47 by kdakota           #+#    #+#             */
/*   Updated: 2021/10/10 16:58:42 by kdakota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memchr(const void *arr, int c, size_t n)
{
	unsigned char	*str;
	unsigned char	sym;

	str = (unsigned char *)arr;
	sym = (unsigned char)c;
	while (n != 0)
	{
		if (*str == sym)
			return (str);
		str++;
		n--;
	}
	return (NULL);
}
