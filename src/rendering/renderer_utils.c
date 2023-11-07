/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-hadr < yel-hadr@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 16:29:31 by bbouagou          #+#    #+#             */
/*   Updated: 2023/11/02 00:38:06 by yel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/renderer.h"

void draw_line(t_data *data, int x1, int y1, int x2, int y2, int color)
{
	int dx;
	int dy;
	int x;
	int y;
	int i;
	int j;
	int xinc;
	int yinc;
	int cumul;

	x = x1;
	y = y1;
	dx = x2 - x1;
	dy = y2 - y1;
	xinc = (dx > 0) ? 1 : -1;
	yinc = (dy > 0) ? 1 : -1;
	dx = abs(dx);
	dy = abs(dy);
	mlx_put_pixel(data->img, x, y, color);
	if (dx > dy)
	{
		cumul = dx / 2;
		i = 1;
		while (i <= dx)
		{
			x += xinc;
			cumul += dy;
			if (cumul >= dx)
			{
				cumul -= dx;
				y += yinc;
			}
			if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
				mlx_put_pixel(data->img, x, y, color);
			i++;
		}
	}
	else
	{
		cumul = dy / 2;
		j = 1;
		while (j <= dy)
		{
			y += yinc;
			cumul += dx;
			if (cumul >= dy)
			{
				cumul -= dy;
				x += xinc;
			}
			if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
				mlx_put_pixel(data->img, x, y, color);
			j++;
		}
	}
}

int	get_rgba(int r, int g, int b, int a)
{ 
    return (r << 24 | g << 16 | b << 8 | a);
}

void ft_error(char	*str)
{
	ft_putstr_fd(str, 2);
	exit(EXIT_FAILURE);
}

void draw_player(t_data *data)
{
	int x;
	int y;
	int xlimit;
	int ylimit;
	
	x = data->camera.player_x -2;
	xlimit = data->camera.player_x + 2;
	ylimit = data->camera.player_y + 2;
	y = data->camera.player_y -2;
	while (y < ylimit)
	{
		x = data->camera.player_x -2;
		while (x < xlimit)
		{
			mlx_put_pixel(data->img, x, y, get_rgba(255, 0, 0, 255));
			x++;
		}
		y++;
	}
}