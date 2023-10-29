/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-hadr < yel-hadr@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 05:38:08 by yel-hadr          #+#    #+#             */
/*   Updated: 2023/10/29 04:00:57 by yel-hadr         ###   ########.fr       */
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
			mlx_put_pixel(data->img, x, y, color);
			j++;
		}
	}
}

void draw_player(t_data data)
{
	int x;
	int y;
	int xlimit;
	int ylimit;
	
	x = data.camera.player_x -2;
	xlimit = data.camera.player_x + 2;
	ylimit = data.camera.player_y + 2;
	y = data.camera.player_y -2;
	while (y < ylimit)
	{
		x = data.camera.player_x -2;
		while (x < xlimit)
		{
			mlx_put_pixel(data.img, x, y, get_rgba(255, 0, 0, 255));
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
			j++;
		}
		i++;
	}
	draw_player(*data);
	draw_line(data, data->camera.player_x, data->camera.player_y, data->camera.player_x + data->camera.dir_x, data->camera.player_y + data->camera.dir_y, get_rgba(255, 0, 0, 255));
}

double	detect_collision(t_data *data, double x, double y)
{
	int	i;
	int	j;

	j = x / data->map.block_width;
	i = y / data->map.block_height;
	if (data->map.map[i][j] == '1')
		return (0);
	return (5);
}

void	key_hook(void *param)
{
	t_data *data = (t_data *)param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_UP))
	{
		data->camera.player_x += data->camera.dir_x;
		data->camera.player_y += data->camera.dir_y;
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_DOWN))
	{
		data->camera.player_x -= data->camera.dir_x;
		data->camera.player_y -= data->camera.dir_y;
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
	{
		data->camera.angle -= 0.1;
		if (data->camera.angle < 0)
			data->camera.angle = 2 * PI;
		data->camera.dir_x = cos(data->camera.angle) * 10;
		data->camera.dir_y = sin(data->camera.angle) * 10;
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
	{
		data->camera.angle += 0.1;
		if (data->camera.angle > 2 * PI)
			data->camera.angle = 0;
		data->camera.dir_x = cos(data->camera.angle) * 10;
		data->camera.dir_y = sin(data->camera.angle) * 10;
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		exit(EXIT_SUCCESS);
	mlx_delete_image(data->mlx, data->img);
	data->img = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	mlx_image_to_window(data->mlx, data->img, 0, 0);
	minimap(data);
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
	mlx_loop_hook(data->mlx, key_hook, data);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
}