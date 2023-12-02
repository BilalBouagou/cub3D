/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_checking_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-hadr < yel-hadr@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 18:56:47 by bbouagou          #+#    #+#             */
/*   Updated: 2023/12/01 22:08:36 by yel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

bool	is_registered(t_list *list, int32_t x, int32_t y)
{
	while (list)
	{
		if (list->x == x && list->y == y)
			return (true);
		list = list->next;
	}
	return (false);
}

bool	valid_coords(t_data	*data, int32_t x, int32_t y, t_list *head)
{
	if (y < 0 || y >= data->map.map_height)
		return (false);
	if (x < 0 || x >= data->map.map_width)
		return (false);
	if (data->map.map[y][x] == '1')
		return (false);
	if (is_registered(head, x, y))
		return (false);
	return (true);
}
