/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 22:55:47 by bbouagou          #+#    #+#             */
/*   Updated: 2023/10/22 09:35:21 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst)
{
	t_list	*current;
	t_list	*tmp;

	if (lst == NULL)
		return ;
	if (*lst != NULL)
	{
		current = *lst;
		while (current != NULL)
		{
			tmp = current;
			current = current->next;
			free(tmp);
		}
		*lst = NULL;
	}
}
