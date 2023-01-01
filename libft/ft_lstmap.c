/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-skim <min-skim@student.42seou.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 13:22:41 by min-skim          #+#    #+#             */
/*   Updated: 2022/12/13 20:13:53 by min-skim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*ret;
	t_list	*tmp;

	ret = NULL;
	while (lst)
	{
		tmp = ft_lstnew((*f)(lst -> content));
		if (!tmp)
		{
			ft_lstclear(&ret, del);
			ft_lstclear(&tmp, del);
			return (NULL);
		}
		ft_lstadd_back(&ret, tmp);
		lst = lst -> next;
	}
	tmp = NULL;
	return (ret);
}
