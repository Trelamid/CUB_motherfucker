/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdakota <kdakota@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 14:20:47 by kdakota           #+#    #+#             */
/*   Updated: 2021/10/09 16:25:38 by kdakota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int	ft_count_w(char const *s, char c)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			n++;
		i++;
	}
	return (n);
}

int	ft_len_w(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
	{
		i++;
	}
	return (i);
}

void	ft_free_all(char **arr, int i)
{
	i = i - 1;
	while (i >= 0)
	{
		free(arr[i]);
		i--;
	}
	free(arr);
}

char	**ft_make_words(char **arr, int c_w, char const *s, char c)
{
	int	i;
	int	n;
	int	j;

	i = -1;
	while (i++ < c_w)
	{
		j = 0;
		while (*s == c)
			s++;
		n = ft_len_w(s, c);
		arr[i] = malloc((n + 1) * sizeof(char));
		if (arr[i] == NULL)
		{
			ft_free_all(arr, i);
			return (NULL);
		}
		while (n-- > 0)
			arr[i][j++] = *s++;
		arr[i][j] = '\0';
	}
	arr[i] = NULL;
	return (arr);
}

char	**ft_split(char const *s, char c)
{
	int		count_w;
	char	**arr;

	if (!s)
		return (NULL);
	count_w = ft_count_w(s, c);
	arr = (char **)malloc((count_w + 1) * sizeof(char *));
	if (arr == NULL)
		return (NULL);
	arr = ft_make_words(arr, count_w - 1, s, c);
	return (arr);
}

//
//int	main()
//{
//	char **arr = ft_split("4123412341234", '4');
//	printf("%s", arr[1]);
//}
