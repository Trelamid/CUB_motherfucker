/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdakota <kdakota@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 14:20:47 by kdakota           #+#    #+#             */
/*   Updated: 2021/10/07 14:20:47 by kdakota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strrchr(const char *str, int ch)
{
	int		len_str;
	char	c;

	c = ch;
	len_str = ft_strlen(str);
	while (len_str != -1 && str[len_str] != c)
		len_str--;
	if (len_str == -1)
		return (NULL);
	while (len_str != 0 && len_str != -1)
	{
		str++;
		len_str--;
	}
	return ((char *)str);
}
