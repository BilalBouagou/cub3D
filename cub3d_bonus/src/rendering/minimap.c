/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 23:41:38 by bbouagou          #+#    #+#             */
/*   Updated: 2023/11/30 23:57:54 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/renderer.h"

void	draw_player(t_data *data)
{
	int	x;
	int	y;

	y = (MINIMAP_HEIGHT / 2) - 4;
	while (y < (MINIMAP_HEIGHT / 2) + 4)
	{
		x = (MINIMAP_WIDTH / 2) - 4;
		while (x < (MINIMAP_WIDTH / 2) + 4)
		{
			mlx_put_pixel(data->minimap_img, x, y, \
				data->textures.ceiling_color);
			x++;
		}
		y++;
	}
}

void	project_on_minimap(t_data *data, int y, int i)
{
	int	x;
	int	j;

	x = data->camera.player_x - (MINIMAP_WIDTH / 2);
	j = 0;
	while (j < MINIMAP_WIDTH)
	{
		if (x < 0 || y < 0)
		{
			mlx_put_pixel(data->minimap_img, j, i, get_rgba(0, 0, 0, 255));
		}
		else
		{
			if (data->map.map[y / BLOCK][x / BLOCK] == '1')
				mlx_put_pixel(data->minimap_img, j, i,
					get_rgba(255, 255, 255, 255));
			else
				mlx_put_pixel(data->minimap_img, j, i,
					get_rgba(173, 216, 230, 255));
		}
		x++;
		j++;
	}
}

void	minimap(t_data *data)
{
	int	y;
	int	i;

	y = data->camera.player_y - (MINIMAP_HEIGHT / 2);
	i = 0;
	while (i < MINIMAP_HEIGHT)
	{
		project_on_minimap(data, y, i);
		y++;
		i++;
	}
	draw_player(data);
}
