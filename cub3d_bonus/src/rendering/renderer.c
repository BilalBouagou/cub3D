/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-hadr < yel-hadr@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 05:38:08 by yel-hadr          #+#    #+#             */
/*   Updated: 2023/11/23 19:55:03 by yel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/renderer.h"


t_direc get_direction( double ray_angle, bool flag)
{
	if (flag)
	{
		if (ray_angle > 0 && ray_angle < PI)
			return (SOUTH);
		else if (ray_angle > PI && ray_angle < 2 * PI)
			return (NORTH);
	}
	else if (!flag)
	{
		if (ray_angle > PI / 2 && ray_angle < 3 * PI / 2)
			return (WEST);
		else if ((ray_angle > 3 * PI / 2 && ray_angle < 2 * PI) || (ray_angle > 0 && ray_angle < PI / 2))
			return (EAST);
	}
	return (NO_DIRECTION);
}

void	ft_draw_rays(t_data *data)
{
	double	ray_angle;
	int		ray;
	t_ray	ray_cast;

	ray_angle = normalize_angle(data->camera.angle - DEGRE * FOV_ANGLE / 2);
	ray = 0;
	while (ray < WINDOW_WIDTH)
	{
		ray_cast = cast_ray(data, ray_angle);
		ray_cast.color = get_rgba(255, 255, 255, 255);
		if (ray_cast.wall != NO_WALL)
			ft_3d_projection(data, ray_cast, ray);
		ray_angle += (double)DEGRE * (double)FOV_ANGLE / (double)WINDOW_WIDTH;
		ray_angle = normalize_angle(ray_angle);
		ray++;
	}
}

void	minimap(t_data *data)
{
	ft_draw_rays(data);
}

void	key_hook(void *param)
{
	t_data *data = (t_data *)param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_UP))
	{
		
		if (!ft_haswallat(data, data->camera.player_x + (data->camera.dir_x * 4), data->camera.player_y + data->camera.dir_y))
		{
			if (!ft_haswallat(data, data->camera.player_x + (data->camera.dir_x * 4), data->camera.player_y) && !ft_haswallat(data, data->camera.player_x, data->camera.player_y +( data->camera.dir_y * 4)))
			{
				data->camera.player_x += data->camera.dir_x;
				data->camera.player_y += data->camera.dir_y;
			}
		}
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_DOWN))
	{
		if (!ft_haswallat(data, data->camera.player_x - data->camera.dir_x, data->camera.player_y - data->camera.dir_y))
		{
			if (!ft_haswallat(data, data->camera.player_x - (data->camera.dir_x * 4), data->camera.player_y) && !ft_haswallat(data, data->camera.player_x, data->camera.player_y - (data->camera.dir_y * 4)))
			{
				data->camera.player_x -= data->camera.dir_x;
				data->camera.player_y -= data->camera.dir_y;
			}
		}
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
	{
		data->camera.angle += 0.01;
		if (data->camera.angle > 2 * PI)
			data->camera.angle -= 2 * PI;
		data->camera.dir_x = cos(data->camera.angle) * SPEED;
		data->camera.dir_y = sin(data->camera.angle) * SPEED;
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
	{
		data->camera.angle -= 0.01;
		if (data->camera.angle < 0)
			data->camera.angle += 2 * PI;
		data->camera.dir_x = cos(data->camera.angle) * SPEED;
		data->camera.dir_y = sin(data->camera.angle) * SPEED;
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
