/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_checking_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 18:56:47 by bbouagou          #+#    #+#             */
/*   Updated: 2023/12/01 15:15:47 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

bool	is_registered(t_list *list, int x, int y)
{
	while (list)
	{
		if (list->x == x && list->y == y)
			return (true);
		list = list->next;
	}
	return (false);
}

bool	valid_coords(t_data	*data, int x, int y, t_list *head)
{
	if (y < 0 || y >= (int) data->map.map_height)
		return (false);
	if (x < 0 || x >= (int)data->map.map_width)
		return (false);
	if (data->map.map[y][x] == '1')
		return (false);
	if (is_registered(head, x, y))
		return (false);
	return (true);
}
