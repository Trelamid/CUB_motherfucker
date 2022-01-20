/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdakota <kdakota@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 14:20:47 by kdakota           #+#    #+#             */
/*   Updated: 2021/10/07 14:21:52 by kdakota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*auf;

	i = 0;
	if (!s)
		return (NULL);
	auf = malloc(ft_strlen(s) + 1);
	if (auf == NULL)
		return (NULL);
	while (s[i])
	{
		auf[i] = f(i, s[i]);
		i++;
	}
	auf[i] = '\0';
	return (auf);
}
