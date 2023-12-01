/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 23:41:38 by bbouagou          #+#    #+#             */
/*   Updated: 2023/12/01 16:28:29 by bbouagou         ###   ########.fr       */
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
				*data->textures.ceiling_color);
			x++;
		}
		y++;
	}
}

void	color_pixels(int mnx, int mny, t_data *data, int color)
{
	mlx_put_pixel(data->minimap_img, mnx, mny, color);
}

void	project_on_minimap(t_data *data, int y, int mny)
{
	int	x;
	int	mnx;

	x = data->camera.player_x - (MINIMAP_WIDTH / 2);
	mnx = 0;
	while (mnx < MINIMAP_WIDTH)
	{
		if (x >= 0 && x / BLOCK < data->map.map_width
			&& y >= 0 && y / BLOCK < data->map.map_height)
		{
			if (data->map.map[y / BLOCK][x / BLOCK] == '1')
				color_pixels(mnx, mny, data, get_rgba(255, 255, 255, 255));
			else if (data->map.map[y / BLOCK][x / BLOCK] == 'D')
				color_pixels(mnx, mny, data, get_rgba(255, 0, 0, 255));
			else if (data->map.map[y / BLOCK][x / BLOCK] == 'O')
				color_pixels(mnx, mny, data, get_rgba(0, 255, 0, 255));
			else
				color_pixels(mnx, mny, data, get_rgba(0, 0, 0, 255));
		}
		else
			mlx_put_pixel(data->minimap_img, mnx, mny, get_rgba(0, 0, 0, 255));
		x++;
		mnx++;
	}
}

void	minimap(t_data *data)
{
	int	y;
	int	mny;

	y = data->camera.player_y - (MINIMAP_HEIGHT / 2);
	mny = 0;
	while (mny < MINIMAP_HEIGHT)
	{
		project_on_minimap(data, y, mny);
		y++;
		mny++;
	}
	draw_player(data);
}
