/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdakota <kdakota@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 20:45:02 by kdakota           #+#    #+#             */
/*   Updated: 2021/10/09 20:45:02 by kdakota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*l1;
	t_list	*l2;

	l1 = *lst;
	if (!*lst)
		return ;
	while (l1)
	{
		l2 = l1->next;
		del(l1->content);
		free(l1);
		l1 = l2;
	}
	*lst = NULL;
}
