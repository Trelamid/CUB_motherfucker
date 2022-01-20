/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdakota <kdakota@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 20:44:57 by kdakota           #+#    #+#             */
/*   Updated: 2021/10/09 20:44:57 by kdakota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*l;

	l = *lst;
	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	while (l->next != NULL)
		l = l->next;
	l->next = new;
}
