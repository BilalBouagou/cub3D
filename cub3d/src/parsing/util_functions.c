/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-hadr < yel-hadr@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 18:52:49 by bbouagou          #+#    #+#             */
/*   Updated: 2023/12/01 22:07:58 by yel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

int32_t	array_len(char **ptr)
{
	int32_t	i;

	i = 0;
	while (ptr && ptr[i])
		i++;
	return (i);
}

void	p_free_resources(char **ptr)
{
	size_t	idx;

	if (ptr)
	{
		idx = 0;
		while (ptr[idx])
		{
			free (ptr[idx]);
			idx++;
		}
		free (ptr);
	}
}
