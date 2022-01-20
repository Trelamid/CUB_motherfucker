/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdakota <kdakota@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 14:20:47 by kdakota           #+#    #+#             */
/*   Updated: 2021/10/07 14:20:47 by kdakota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;
	char	*arrd;
	char	*arrs;

	i = 0;
	arrd = (char *)dst;
	arrs = (char *)src;
	if (arrd == NULL && arrs == NULL)
		return (NULL);
	if (arrd > arrs && len != 0)
	{
		while (len-- > 0)
			arrd[len] = arrs[len];
	}
	else
	{
		while (i < len)
		{
			arrd[i] = arrs[i];
			i++;
		}
	}
	return (dst);
}
