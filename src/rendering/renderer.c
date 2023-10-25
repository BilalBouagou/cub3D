/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 13:26:05 by bbouagou          #+#    #+#             */
/*   Updated: 2023/10/25 05:33:56 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/renderer.h"

int	get_rgba(int r, int g, int b, int a)
{ 
    return (r << 24 | g << 16 | b << 8 | a);
}

// void	draw_circle(t_data *data, size_t i, size_t j)
// {
	
// }

void	fill_img(t_data *data, uint32_t x, uint32_t y, int color)
{
	size_t	xm;
	size_t	ym;
	size_t	ylimit;
	size_t	xlimit;

	ym = y * data->map.block_height;
	ylimit = ((y * data->map.block_height) + data->map.block_height);
	xlimit = ((x * data->map.block_width) + data->map.block_width);
	while (ym < ylimit)
	{
		xm = x * data->map.block_width;
		while (xm < xlimit)
		{
			// mlx_put_pixel(data->img, xm, ym, color);
			xm++;
		}
		mlx_put_pixel(data->img, xm, ym, get_rgba(255, 0, 0, 255));
		ym++;
	}
	mlx_put_pixel(data->img, xm, ym, get_rgba(255, 0, 0, 255));
}

void	minimap(t_data *data)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (data->map.map[i])
	{
		j = 0;
		while(data->map.map[i][j])
		{
			if (data->map.map[i][j] == '1')
				fill_img(data, j, i, get_rgba(255, 255, 255, 255));
			else
				fill_img(data, j, i, get_rgba(0, 0, 0, 255));
			// if (data->map.map[i][j] == 'N' || data->map.map[i][j] == 'S' || data->map.map[i][j] == 'E' || data->map.map[i][j] == 'W')
			// 	draw_circle(data, i, j);
			j++;
		}
		i++;
	}
}

void	renderer(t_data *data)
{
	data->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D", false);
	if (!data->mlx)
		exit(printf(MLXINITERR));
	data->img = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!data->img)
		exit(printf(MLXIMGERR));
	minimap(data);
	mlx_image_to_window(data->mlx, data->img, 0, 0);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
}