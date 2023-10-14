/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 13:26:05 by bbouagou          #+#    #+#             */
/*   Updated: 2023/08/30 16:31:25 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/renderer.h"

int get_rgba(int r, int g, int b, int a)
{ 
    return (r << 24 | g << 16 | b << 8 | a);
}

void print_arr(char **ptr)
{
	size_t idx;

	idx = 0;
	while (ptr && ptr[idx])
	{
		printf("%s\n", ptr[idx]);
		idx++;
	}
}

void	fill_img(mlx_image_t* img, uint32_t x, uint32_t y, int color, t_data *data)
{
	size_t	xm;
	size_t	ym;
	size_t	ylimit;
	size_t	xlimit;

	ym = y * data->map.block_length;
	ylimit = ((y * data->map.block_length) + data->map.block_length);
	if (ft_strchr("NSWE", data->map.map[y][x]))
	{
		ym = ((y * data->map.block_length) + (data->map.block_length / 5 * 2));
		ylimit = ((y * data->map.block_length) + (data->map.block_length / 5 * 3));
	}
	while (ym < ylimit)
	{
		xm = x * data->map.block_width;
		xlimit = ((x * data->map.block_width) + data->map.block_width);
		if (ft_strchr("NSWE", data->map.map[y][x]))
		{
			xm = ((x * data->map.block_width) + (data->map.block_width / 5 * 2));
			xlimit = ((x * data->map.block_width) + (data->map.block_width / 5 * 3));
		}
		while (xm < xlimit)
		{
			mlx_put_pixel(img, xm, ym, color);
			xm++;
		}
		ym++;
	}
}

int does_intersect(unsigned int x, unsigned int y, t_data *data)
{
}

/*
y2 = (x2 - x1) * slope + y1
*/

/*
d=√((x2 – x1)² + (y2 – y1)²)
*/
void    draw_line(mlx_image_t* img, t_data *data, double angle, int index)
{
}

void	brah(t_data *data)
{
	size_t			x;
	size_t			y;
	size_t			i;
	y = 0;
	data->img = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_HIGHT);
	while (data->map.map[y])
	{
		x = 0;
		while (data->map.map[y][x])
		{
			if (data->map.map[y][x] == '1')
				fill_img(data->img, x, y, get_rgba(255, 255, 255, 255), data);
			else if (ft_strchr("NSWE", data->map.map[y][x]))
				fill_img(data->img, x, y, get_rgba(255, 0, 0, 255), data);
			x++;
		}
		y++;
	}
	mlx_image_to_window(data->mlx, data->img, 0, 0);
}

void	input_handle(mlx_key_data_t keydata, void *param)
{
	t_data* data;

	data = (t_data*)param;
	mlx_delete_image(data->mlx, data->img);
	brah(data);
	
}

void	renderer(t_data *data)
{
	data->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HIGHT, "cub3D", false);
	if (!data->mlx)
	{
		printf("%s", mlx_strerror(mlx_errno));
		exit(EXIT_FAILURE);
	}
	brah(data);
	mlx_key_hook(data->mlx, input_handle, (void *)data);
	mlx_loop(data->mlx);
}
