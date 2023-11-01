/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-hadr < yel-hadr@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 05:38:08 by yel-hadr          #+#    #+#             */
/*   Updated: 2023/11/02 00:53:01 by yel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/renderer.h"

void	fill_img(t_data *data, uint32_t x, uint32_t y, int color)
{
	size_t	xm;
	size_t	ym;
	size_t	ylimit;
	size_t	xlimit;
	(void)color;

	ym = y * data->map.block_height + 1;
	ylimit = ((y * data->map.block_height) + data->map.block_height);
	xlimit = ((x * data->map.block_width) + data->map.block_width);
	while (ym < ylimit)
	{
		xm = x * data->map.block_width + 1; 
		while (xm < xlimit)
		{
			if (xm < xlimit - 1  && ym < ylimit -1)
				mlx_put_pixel(data->img, xm, ym, color);
			xm++;
		}
		ym++;
	}
}

float	distance(float x1, float y1, float x2, float y2)
{
	return (sqrtf((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

void	ft_draw_rays(t_data *data)
{
	int r;
	int mx;
	int my;
	int mp;
	int dof;
	float rx;
	float ry;
	double ra;
	float xo;
	float yo;
	
	ra = data->camera.angle - 30 * DEGRE;
	if (ra < 0)
		ra += 2 * PI;
	if (ra > 2 * PI)
		ra -= 2 * PI;
	r = 0;
	while(r < WINDOW_WIDTH)
	{
		dof = 0;
		float atan = -1/tan(ra);
		float disH = 1000000, hx = data->camera.player_x, hy = data->camera.player_y;
		if (ra > PI)
		{
			ry = (((int)data->camera.player_y / 32 ) * 32) - 0.0001;
			rx = (data->camera.player_y - ry) * atan + data->camera.player_x;
			yo = -32;
			xo = -yo * atan;
		}
		if (ra < PI)
		{
			ry = (((int)data->camera.player_y / 32 ) * 32) + 32;
			rx = (data->camera.player_y - ry) * atan + data->camera.player_x;
			yo = 32;
			xo = -yo * atan;
		}
		if (ra == 0 || ra == PI)
		{
			rx = data->camera.player_x;
			ry = data->camera.player_y;
			dof = 100;
		}
		while (dof < 100)
		{
			mx = (int)(rx) / 32;
			my = (int)(ry) / 32;
			if (mx < 0 || mx > (int)data->map.map_width || my < 0 || my > (int)data->map.map_height)
				break;
			mp = my * data->map.map_width + mx;
			if (mp >= 0 && mp <= (int)(data->map.map_width * data->map.map_height) && data->map.map[my][mx] == '1')
			{
				hx = rx;
				hy = ry;
				disH = distance(data->camera.player_x, data->camera.player_y, hx, hy);
				dof = 100;
			}
			else
			{
				rx += xo;
				ry += yo;
				dof++;
			}
		}
		dof = 0;
		float	ntan = -tan(ra);
		float disV = 1000000, vx = data->camera.player_x, vy = data->camera.player_y;
		if (ra > PI / 2 && ra < 3 * PI / 2)
		{
			rx = (((int)data->camera.player_x / 32) * 32) - 0.0001;
			ry = (data->camera.player_x - rx) * ntan + data->camera.player_y;
			xo = -32;
			yo = -xo * ntan;
		}
		if (ra < PI / 2 || ra > 3 * PI / 2)
		{
			rx = (((int)data->camera.player_x / 32) * 32) + 32;
			ry = (data->camera.player_x - rx) * ntan + data->camera.player_y;
			xo = 32;
			yo = -xo * ntan;
		}
		if (ra == 0 || ra == PI)
		{
			rx = data->camera.player_x;
			ry = data->camera.player_y;
			dof = 100;
		}
		while (dof < 100)
		{
			mx = (int)(rx) / 32;
			if (mx < 0 || mx > (int)data->map.map_width)
				break;
			my = (int)(ry) / 32;
			if (my < 0 || my > (int)data->map.map_height)
				break;
			mp = my * data->map.map_width + mx;
			if (mp > 0 && mp < (int)(data->map.map_width * data->map.map_height) && data->map.map[my][mx] == '1')
			{
				vx = rx;
				vy = ry;
				disV = distance(data->camera.player_x, data->camera.player_y, vx, vy);
				dof = 100;
			}
			else
			{
				rx += xo;
				ry += yo;
				dof++;
			}
		}
		if (disV < disH)
			draw_line(data, data->camera.player_x, data->camera.player_y, vx, vy, get_rgba(255, 0, 0, 255));
		else
			draw_line(data, data->camera.player_x, data->camera.player_y, hx, hy, get_rgba(255, 0, 24, 255));
		ra += DEGRE / RAYS_NUMBER;
		if (ra < 0)
			ra += 2 * PI;
		if (ra > 2 * PI)
			ra -= 2 * PI;
		r++;
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
	ft_draw_rays(data);
}

void	key_hook(void *param)
{
	t_data *data = (t_data *)param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_UP))
	{
		
		if (data->map.map[(int)(data->camera.player_y + data->camera.dir_y) / 32][(int)(data->camera.player_x + data->camera.dir_x) / 32] != '1')
		{
			data->camera.player_x += data->camera.dir_x;
			data->camera.player_y += data->camera.dir_y;
		}
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_DOWN))
	{
		if (data->map.map[(int)(data->camera.player_y - data->camera.dir_y) / 32][(int)(data->camera.player_x - data->camera.dir_x) / 32] != '1')
		{
			data->camera.player_x -= data->camera.dir_x;
			data->camera.player_y -= data->camera.dir_y;
		}
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
	{
		data->camera.angle += 0.01;
		if (data->camera.angle > 2 * PI)
			data->camera.angle = 0.00001;
		data->camera.dir_x = cos(data->camera.angle) * 5;
		data->camera.dir_y = sin(data->camera.angle) * 5;
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
	{
		data->camera.angle -= 0.01;
		if (data->camera.angle < 0)
			data->camera.angle = 2 * PI;
		data->camera.dir_x = cos(data->camera.angle) * 5;
		data->camera.dir_y = sin(data->camera.angle) * 5;
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