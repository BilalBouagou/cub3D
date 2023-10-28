/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 05:38:08 by yel-hadr          #+#    #+#             */
/*   Updated: 2023/10/28 05:14:23 by bbouagou         ###   ########.fr       */
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
	mlx_put_pixel(data->img, data->camera.player_x, data->camera.player_y, get_rgba(255, 0, 0, 255));
}

double	detect_collision(t_data *data, double x, double y)
{
	int	i;
	int	j;

	j = x / data->map.block_width;
	i = y / data->map.block_height;
	if (data->map.map[i][j] == '1')
		return (0);
	return (2);
}

void	draw_line(t_data *data, int i)
{
	double	x;
	double	y;

	x = data->camera.player_x;
	y = data->camera.player_y;
	while (data->map.map[(int)(y / data->map.block_width)][(int)(x / data->map.block_height)] != '1')
	{
		mlx_put_pixel(data->img, x, y, get_rgba(255, 0, 0, 255));
		x += data->ray[i].dir_x;
		y += data->ray[i].dir_y;
	}
}

void	raycaster(t_data *data)
{
	int i;
	int		mapX, mapY;

	i = 0;
	while (i < WINDOW_WIDTH)
	{
		mapX = data->camera.player_x / data->map.block_width;
		mapY = data->camera.player_y / data->map.block_height;
		data->ray[i].cam_x = (2 * i / (double)WINDOW_WIDTH) - 1;
		data->ray[i].dir_x = data->camera.dir_x + data->camera.plane_x * data->ray[i].cam_x;
		data->ray[i].dir_y = data->camera.dir_y + data->camera.plane_y * data->ray[i].cam_x;
		data->ray[i].deltaDistX = fabs(1 / data->ray[i].dir_x);
		data->ray[i].deltaDistY = fabs(1 / data->ray[i].dir_y);

		if (data->ray[i].dir_x < 0)
		{
			data->ray[i].stepX = -1;
			data->ray[i].sideDistX = (data->camera.player_x - mapX) * data->ray[i].deltaDistX;
		}
		else
		{
			data->ray[i].stepX = 1;
			data->ray[i].sideDistX = (mapX + 1.0 - data->camera.player_x) * data->ray[i].deltaDistX;
		}

		if (data->ray[i].dir_y < 0)
		{
			data->ray[i].stepY = -1;
			data->ray[i].sideDistY = (data->camera.player_y - mapY) * data->ray[i].deltaDistY;
		}
		else
		{
			data->ray[i].stepY = 1;
			data->ray[i].sideDistY = (mapY + 1.0 - data->camera.player_y) * data->ray[i].deltaDistY;
		}
		
		while (data->ray[i].wallHit == false)
		{
			if (data->ray[i].sideDistX < data->ray[i].sideDistY)
			{
				data->ray[i].sideDistX += data->ray[i].deltaDistX;
				mapX += data->ray[i].stepX;
				data->ray[i].side = 0;
			}
			else
			{
				data->ray[i].sideDistY += data->ray[i].deltaDistY;
				mapY += data->ray[i].stepY;
				data->ray[i].side = 1;	
			}

			if (data->map.map[mapY][mapX] == '1')
				data->ray[i].wallHit = true;
		}

		if (data->ray[i].side == 0)
			data->ray[i].perpWallDist = data->ray[i].sideDistX - data->ray[i].deltaDistX;
		else
			data->ray[i].perpWallDist = data->ray[i].sideDistY - data->ray[i].deltaDistY;
		draw_line(data, i);
		i++;
	}
}

void	key_hook(void *param)
{
	t_data *data = (t_data *)param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_UP))
	{
		data->camera.player_x += data->camera.dir_x * detect_collision(data, data->camera.player_x + data->camera.dir_x * 2, data->camera.player_y);
		data->camera.player_y += data->camera.dir_y * detect_collision(data, data->camera.player_x, data->camera.player_y + data->camera.dir_y * 2);
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_DOWN))
	{
		data->camera.player_x -= data->camera.dir_x * detect_collision(data, data->camera.player_x - data->camera.dir_x * 2, data->camera.player_y);
		data->camera.player_y -= data->camera.dir_y * detect_collision(data, data->camera.player_x, data->camera.player_y - data->camera.dir_y * 2);
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
	{
		double oldDirX = data->camera.dir_x;
		data->camera.dir_x = data->camera.dir_x * cos((5 * DEGRE)) - data->camera.dir_y * sin((5 * DEGRE));
		data->camera.dir_y = oldDirX * sin((5 * DEGRE)) + data->camera.dir_y * cos((5 * DEGRE));
		double oldPlaneX = data->camera.plane_x;
		data->camera.plane_x = data->camera.plane_x * cos((5 * DEGRE)) - data->camera.plane_y * sin((5 * DEGRE));
		data->camera.plane_y = oldPlaneX * sin((5 * DEGRE)) + data->camera.plane_y * cos((5 * DEGRE));
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
	{
		double oldDirX = data->camera.dir_x;
		data->camera.dir_x = data->camera.dir_x * cos(-(5 * DEGRE)) - data->camera.dir_y * sin(-(5 * DEGRE));
		data->camera.dir_y = oldDirX * sin(-(5 * DEGRE)) + data->camera.dir_y * cos(-(5 * DEGRE));
		double oldPlaneX = data->camera.plane_x;
		data->camera.plane_x = data->camera.plane_x * cos(-(5 * DEGRE)) - data->camera.plane_y * sin(-(5 * DEGRE));
		data->camera.plane_y = oldPlaneX * sin(-(5 * DEGRE)) + data->camera.plane_y * cos(-(5 * DEGRE));
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		exit(EXIT_SUCCESS);
	mlx_delete_image(data->mlx, data->img);
	data->img = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	mlx_image_to_window(data->mlx, data->img, 0, 0);
	minimap(data);
	raycaster(data);
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
	raycaster(data);
	mlx_image_to_window(data->mlx, data->img, 0, 0);
	mlx_loop_hook(data->mlx, key_hook, data);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
}