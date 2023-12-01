/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_manip.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 19:05:24 by bbouagou          #+#    #+#             */
/*   Updated: 2023/12/01 14:38:20 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

void	player_pos_detector(t_data *data, int idx, int idx2, bool *flag)
{
	if (data->map.map[idx][idx2] == 'N')
		data->camera.angle = 3 * M_PI / 2;
	else if (data->map.map[idx][idx2] == 'S')
		data->camera.angle = M_PI / 2;
	else if (data->map.map[idx][idx2] == 'W')
		data->camera.angle = M_PI;
	else if (data->map.map[idx][idx2] == 'E')
		data->camera.angle = 0;
	data->camera.player_x = idx2;
	data->camera.player_y = idx;
	*flag = true;
}

void	check_map_components(t_data *data)
{
	bool	flag;
	int		idx;
	int		idx2;

	idx = 0;
	flag = false;
	while (data->map.map[idx])
	{
		idx2 = 0;
		while (data->map.map[idx][idx2])
		{
			if (ft_strchr("NSWE", data->map.map[idx][idx2]) && flag == true)
				exit(printf(PLYRPOSERR));
			if (ft_strchr("NSWE", data->map.map[idx][idx2]) && flag == false)
			{
				player_pos_detector(data, idx, idx2, &flag);
			}
			if (char_is_whitespace(data->map.map[idx][idx2]))
				data->map.map[idx][idx2] = '0';
			idx2++;
		}
		idx++;
	}
	if (flag == false)
		exit(printf(NOPLYPOSERR));
}

void	check_map_borders(t_data *data)
{
	t_list	*head;
	t_list	*curr;

	head = ft_lstnew(data->camera.player_x / BLOCK,
			data->camera.player_y / BLOCK);
	curr = head;
	while (curr)
	{
		if (curr->x == 0 || curr->y == 0 || curr->x == data->map.map_width - 1
			|| curr->y == data->map.map_height - 1)
			exit(printf(MAPSTRTERR));
		if (valid_coords(data, curr->x + 1, curr->y, head))
			ft_lstadd_back(&head, ft_lstnew(curr->x + 1, curr->y));
		if (valid_coords(data, curr->x - 1, curr->y, head))
			ft_lstadd_back(&head, ft_lstnew(curr->x - 1, curr->y));
		if (valid_coords(data, curr->x, curr->y + 1, head))
			ft_lstadd_back(&head, ft_lstnew(curr->x, curr->y + 1));
		if (valid_coords(data, curr->x, curr->y - 1, head))
			ft_lstadd_back(&head, ft_lstnew(curr->x, curr->y - 1));
		curr = curr->next;
	}
	ft_lstclear(&head);
}
