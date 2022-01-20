/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdakota <kdakota@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 14:20:47 by kdakota           #+#    #+#             */
/*   Updated: 2021/10/07 14:20:47 by kdakota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_memcmp(const void *arr1, const void *arr2, size_t n)
{
	unsigned char	*ar1;
	unsigned char	*ar2;
	size_t			nn;

	ar1 = (unsigned char *)arr1;
	ar2 = (unsigned char *)arr2;
	nn = 0;
	while (nn != n)
	{
		if (ar1[nn] != ar2[nn])
			return (ar1[nn] - ar2[nn]);
		nn++;
	}
	return (0);
}
