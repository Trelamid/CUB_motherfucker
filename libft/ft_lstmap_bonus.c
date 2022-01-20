/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdakota <kdakota@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 20:45:09 by kdakota           #+#    #+#             */
/*   Updated: 2021/10/10 03:37:12 by kdakota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*start;
	t_list	*auf;

	if (!lst || !f)
		return (NULL);
	start = ft_lstnew(f(lst->content));
	lst = lst->next;
	while (lst)
	{
		auf = ft_lstnew(f(lst->content));
		if (auf == NULL)
		{
			ft_lstclear(&start, del);
			return (start);
		}
		ft_lstadd_back(&start, auf);
		lst = lst->next;
	}
	return (start);
}
