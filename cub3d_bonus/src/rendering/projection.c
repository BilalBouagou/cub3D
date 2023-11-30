/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-hadr < yel-hadr@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 19:42:57 by yel-hadr          #+#    #+#             */
/*   Updated: 2023/11/30 21:32:50 by yel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/renderer.h"

void	draw_line(t_data *data, t_ray ray, int x)
{
	int32_t	y;

	y = 0;
	while (y <= ray.wall_top)
		mlx_put_pixel(data->img, x, y++, data->textures.ceiling_color);
	while (ray.wall_bottom < WINDOW_HEIGHT)
		mlx_put_pixel(data->img, x, ray.wall_bottom++, \
			data->textures.floor_color);
}

void	draw_walls(t_data *data, t_ray ray, int x)
{
	while (ray.wall_top < ray.wall_bottom)
	{
		if (ray.is_door == DOOR)
			mlx_put_pixel(data->img, x, ray.wall_top, \
				get_texture(ray, data->doors));
		else if (ray.wall == VERTICAL)
		{
			if (ray.east_west == EAST)
				mlx_put_pixel(data->img, x, ray.wall_top, \
					get_texture(ray, data->east));
			else
				mlx_put_pixel(data->img, x, ray.wall_top, \
					get_texture(ray, data->west));
		}
		else
		{
			if (ray.north_south == NORTH)
				mlx_put_pixel(data->img, x, ray.wall_top, \
					get_texture(ray, data->north));
			else
				mlx_put_pixel(data->img, x, ray.wall_top, \
					get_texture(ray, data->south));
		}
		ray.wall_top++;
	}
}

void	ft_3d_projection(t_data *data, t_ray ray, int x)
{
	ray.wall_strip_height = (BLOCK / ray.distance) * DISTANCE_PROJ_PLANE;
	ray.wall_top = (WINDOW_HEIGHT / 2) - (ray.wall_strip_height / 2);
	if (ray.wall_top < 0)
		ray.wall_top = 0;
	ray.wall_bottom = (WINDOW_HEIGHT / 2) + (ray.wall_strip_height / 2);
	if (ray.wall_bottom > WINDOW_HEIGHT)
		ray.wall_bottom = WINDOW_HEIGHT;
	if (ray.wall == VERTICAL)
		ray.offset_x = (int)ray.dir_y % BLOCK;
	else
		ray.offset_x = (int)ray.dir_x % BLOCK;
	if (ray.wall_top > 0 || ray.wall_bottom < WINDOW_HEIGHT)
		draw_line(data, ray, x);
	draw_walls(data, ray, x);
}
