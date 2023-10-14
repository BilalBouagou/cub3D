/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 11:25:44 by bbouagou          #+#    #+#             */
/*   Updated: 2023/08/22 22:29:12 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

void	p_free_resources(char **ptr)
{
	size_t idx;

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

int		array_len(char **ptr)
{
	int	i;

	i = 0;
	while (ptr && ptr[i])
		i++;
	return (i);
}