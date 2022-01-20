/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdakota <kdakota@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 14:20:47 by kdakota           #+#    #+#             */
/*   Updated: 2021/10/10 16:44:39 by kdakota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t num)
{
	char	*src2;
	size_t	ret;
	size_t	i;
	size_t	len_dst;
	size_t	len_src;

	i = 0;
	src2 = (char *)src;
	len_dst = ft_strlen(dst);
	len_src = ft_strlen(src2);
	if (num > len_dst)
		ret = len_dst + len_src;
	else
		return (ret = len_src + num);
	while (src[i] && len_dst + 1 < num)
	{
		dst[len_dst++] = src[i++];
	}
	dst[len_dst] = '\0';
	return (ret);
}
