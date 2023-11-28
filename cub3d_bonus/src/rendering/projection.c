/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-hadr < yel-hadr@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 19:42:57 by yel-hadr          #+#    #+#             */
/*   Updated: 2023/11/28 19:59:44 by yel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/renderer.h"



void draw_walls(t_data *data, t_ray ray, int x)
{
	while (ray.wall_top < ray.wall_bottom)
	{
		if (ray.is_door == DOOR)
			mlx_put_pixel(data->img, x, ray.wall_top, ft_get_texture_color(ray, data->doors));
		else if (ray.wall == VERTICAL)
		{
			if (ray.east_west == EAST)
				mlx_put_pixel(data->img, x, ray.wall_top, ft_get_texture_color(ray, data->east));
			else
				mlx_put_pixel(data->img, x, ray.wall_top, ft_get_texture_color(ray, data->west));
		}
		else
		{
			if (ray.north_south == NORTH)
				mlx_put_pixel(data->img, x, ray.wall_top, ft_get_texture_color(ray, data->north));
			else
				mlx_put_pixel(data->img, x, ray.wall_top, ft_get_texture_color(ray, data->south));
		}
		ray.wall_top++;
	}
}

void	ft_3d_projection(t_data *data, t_ray ray, int x)
{
	ray.wall_strip_height = (BLOCK / ray.distance) * DISTANCE_PROJ_PLANE;
	ray.wall_top = (WINDOW_HEIGHT / 2) - (ray.wall_strip_height / 2);
	ray.wall_top = ray.wall_top < 0 ? 0 : ray.wall_top;
	ray.wall_bottom = (WINDOW_HEIGHT / 2) + (ray.wall_strip_height / 2);
	ray.wall_bottom = ray.wall_bottom > WINDOW_HEIGHT ? WINDOW_HEIGHT : ray.wall_bottom;
	if (ray.wall == VERTICAL)
		ray.offset_x = (int)ray.dir_y % BLOCK;
	else
		ray.offset_x = (int)ray.dir_x % BLOCK;
	if (ray.wall_top > 0)
		draw_line(data, x, 0, x, ray.wall_top, get_rgba(100, 150, 50, 255));
	draw_walls(data, ray, x);
	if (ray.wall_bottom < WINDOW_HEIGHT)
		draw_line(data, x, ray.wall_bottom, x, WINDOW_HEIGHT, get_rgba(150, 150, 150, 255));
}