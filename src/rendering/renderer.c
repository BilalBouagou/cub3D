/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 05:38:08 by yel-hadr          #+#    #+#             */
/*   Updated: 2023/10/26 02:04:52 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/renderer.h"

int	get_rgba(int r, int g, int b, int a)
{ 
    return (r << 24 | g << 16 | b << 8 | a);
}

void ft_error(char	*str)
{
	ft_putstr_fd(str, 2);
	exit(EXIT_FAILURE);
}

void	draw_camera(t_data *data, size_t i, size_t j)
{
	size_t	x;
	size_t	y;
	size_t	xlimit;
	size_t	ylimit;

	x = (j * data->map.block_width) + data->map.block_width / 3;
	y = (i * data->map.block_height) + data->map.block_height / 3;
	xlimit = (j * data->map.block_width) + ((data->map.block_width / 3) * 2);
	ylimit = (i * data->map.block_height) + ((data->map.block_height / 3) * 2);
	while (y < ylimit)
	{
		x = (j * data->map.block_width) + data->map.block_width / 3;
		while (x < xlimit)
		{
			mlx_put_pixel(data->img, x, y, get_rgba(255, 0, 0, 255));
			x++;
		}
		y++;
	}	
}

void	fill_img(t_data *data, uint32_t x, uint32_t y, int color)
{
	size_t	xm;
	size_t	ym;
	size_t	ylimit;
	size_t	xlimit;
	(void)color;

	ym = y * data->map.block_height;
	ylimit = ((y * data->map.block_height) + data->map.block_height);
	xlimit = ((x * data->map.block_width) + data->map.block_width);
	while (ym < ylimit)
	{
		xm = x * data->map.block_width; 
		while (xm < xlimit)
		{
			if (xm < xlimit - 2  && ym < ylimit -2)
			{
				mlx_put_pixel(data->img, xm, ym, color);
			}
			else
				mlx_put_pixel(data->img, xm, ym, 0);
			xm++;
		}
		ym++;
	}

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
				fill_img(data, j, i, get_rgba(100, 150, 50, 255));
			else
				fill_img(data, j, i, get_rgba(0, 0, 0, 255));
			if (ft_strchr("NSWE", data->map.map[i][j]))
				draw_camera(data, i, j);
			j++;
		}
		i++;
	}
}

void	renderer(t_data *data)
{
	data->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D", false);
	if (!data->mlx)
		ft_error((char *)mlx_strerror(mlx_errno));
	data->img = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!data->img)
		ft_error((char *)mlx_strerror(mlx_errno));
	minimap(data);
	mlx_image_to_window(data->mlx, data->img, 0, 0);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
}