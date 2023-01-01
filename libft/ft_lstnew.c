/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-skim <min-skim@student.42seou.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 13:22:43 by min-skim          #+#    #+#             */
/*   Updated: 2022/12/13 20:15:15 by min-skim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*ptr;

	ptr = (t_list *)malloc(sizeof(t_list));
	if (!ptr)
		return (NULL);
	ptr ->content = content;
	ptr -> next = NULL;
	return (ptr);
}
