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

void	fill_img(t_data *data, uint32_t x, uint32_t y, uint32_t color)
{
	size_t	xm;
	size_t	ym;
	size_t	ylimit;
	size_t	xlimit;
	(void)color;

	ym = y * BLOCK + 1;
	ylimit = ((y * BLOCK) + BLOCK);
	xlimit = ((x * BLOCK) + BLOCK);
	while (ym < ylimit)
	{
		xm = x * BLOCK + 1; 
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
	double	ray_angle;
	int		ray;

	ray_angle = data->camera.angle - (30 * DEGRE);
	ray = 0;
	while (ray < 1)
	{
		ray++;
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
		
		if (data->map.map[(int)(data->camera.player_y + data->camera.dir_y) / BLOCK][(int)(data->camera.player_x + data->camera.dir_x) / BLOCK] != '1')
		{
			data->camera.player_x += data->camera.dir_x;
			data->camera.player_y += data->camera.dir_y;
		}
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_DOWN))
	{
		if (data->map.map[(int)(data->camera.player_y - data->camera.dir_y) / BLOCK][(int)(data->camera.player_x - data->camera.dir_x) / BLOCK] != '1')
		{
			data->camera.player_x -= data->camera.dir_x;
			data->camera.player_y -= data->camera.dir_y;
		}
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
	{
		data->camera.angle += 0.01;
		if (data->camera.angle > 2 * PI)
			data->camera.angle -= 2 * PI;
		data->camera.dir_x = cos(data->camera.angle) * 5;
		data->camera.dir_y = sin(data->camera.angle) * 5;
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
	{
		data->camera.angle -= 0.01;
		if (data->camera.angle < 0)
			data->camera.angle += 2 * PI;
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