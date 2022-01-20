/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdakota <kdakota@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 14:20:47 by kdakota           #+#    #+#             */
/*   Updated: 2021/10/07 14:20:47 by kdakota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t num)
{
	unsigned int	ret;
	unsigned int	i;

	ret = 0;
	i = 0;
	while (src[ret])
		ret++;
	if (num == 0)
		return (ret);
	while (src[i] && i < (num - 1))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ret);
}
