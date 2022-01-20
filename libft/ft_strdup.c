/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdakota <kdakota@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 14:20:47 by kdakota           #+#    #+#             */
/*   Updated: 2021/10/07 14:20:47 by kdakota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *s1)
{
	char	*str;
	size_t	i;

	str = (char *)malloc((ft_strlen(s1) + 1) * sizeof(*str));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = s1[i];
	return (str);
}
