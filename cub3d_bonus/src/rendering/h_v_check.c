/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_v_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-hadr < yel-hadr@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 19:41:47 by yel-hadr          #+#    #+#             */
/*   Updated: 2023/11/28 19:55:05 by yel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/renderer.h"

t_ray horizontal_check(t_data *data, double ray_angle)
{
	double	yintercept, xintercept;
	double	xstep, ystep;
	t_ray	ray_h;
	// horizontal ray-grid intersection code
	ray_h.north_south = get_direction(ray_angle, true);
	ray_h.east_west = get_direction(ray_angle, false);
	ray_h.is_door = NO_DIRECTION;
	ray_h.distance = INT_MAX;

	// find the y-coordinat and the x-coordinat of the first horizontal grid line we are going to hit
	yintercept = floor(data->camera.player_y / BLOCK) * BLOCK;
	yintercept += ray_h.north_south == SOUTH ? BLOCK : 0;
	xintercept = data->camera.player_x + (yintercept - data->camera.player_y) / tan(ray_angle);

	// calculate the increment xstep and ystep
	ystep = BLOCK;
	ystep *= ray_h.north_south == NORTH ? -1 : 1;
	xstep = BLOCK / tan(ray_angle);
	xstep *= (ray_h.east_west == WEST && xstep > 0) ? -1 : 1;
	xstep *= (ray_h.east_west == EAST && xstep < 0) ? -1 : 1;

	// find the next horizontal intersection
	double next_horz_x = xintercept;
	double next_horz_y = yintercept;
	while (next_horz_x >= 0 && next_horz_x <= (int) data->map.map_width * BLOCK && next_horz_y >= 0 && next_horz_y <= (int) data->map.map_height * BLOCK)
	{
		double x_to_check = next_horz_x;
		double y_to_check = next_horz_y + (ray_h.north_south == NORTH ? -1 : 0);
		if (ft_haswallat(data, x_to_check, y_to_check))
		{
			if (ft_hasdoor(data, x_to_check, y_to_check))
				ray_h.is_door = DOOR;
			ray_h.distance = distance(data->camera.player_x, data->camera.player_y, next_horz_x, next_horz_y);
			ray_h.distance *= cos(normalize_angle(ray_angle - data->camera.angle));
			ray_h.dir_x = next_horz_x;
			ray_h.dir_y = next_horz_y;
			ray_h.wall = HORIZONTAL;
			break ;
		}
		else
		{
			next_horz_x += xstep;
			next_horz_y += ystep;
		}
	}
	return ray_h;
}

t_ray	vertical_check(t_data *data, double ray_angle)
{
	double	yintercept, xintercept;
	double	xstep, ystep;
	t_ray	ray_v;
	// vertical ray-grid intersection code
	ray_v.north_south = get_direction(ray_angle, true);
	ray_v.east_west = get_direction(ray_angle, false);
	ray_v.is_door = NO_DIRECTION;
	ray_v.distance = INT_MAX;
	// find the x-coordinat and the y-coordinat of the first vertical grid line we are going to hit
	xintercept = floor(data->camera.player_x / BLOCK) * BLOCK;
	xintercept += ray_v.east_west == EAST ? BLOCK : 0;
	yintercept = data->camera.player_y + (xintercept - data->camera.player_x) * tan(ray_angle);
	// calculate the increment xstep and ystep
	xstep = BLOCK;
	xstep *= ray_v.east_west == WEST ? -1 : 1;
	ystep = BLOCK * tan(ray_angle);
	ystep *= (ray_v.north_south == NORTH && ystep > 0) ? -1 : 1;
	ystep *= (ray_v.north_south == SOUTH && ystep < 0) ? -1 : 1;
	// find the next vertical intersection
	double next_vert_x = xintercept;
	double next_vert_y = yintercept;
	while (next_vert_x >= 0 && next_vert_x <= data->map.map_width * BLOCK && next_vert_y >= 0 && next_vert_y <= data->map.map_height * BLOCK)
	{
		double x_to_check = next_vert_x + (ray_v.east_west == WEST ? -1 : 0);
		double y_to_check = next_vert_y;
		if (ft_haswallat(data, x_to_check, y_to_check))
		{
			if (ft_hasdoor(data, x_to_check, y_to_check))
				ray_v.is_door = DOOR;
			ray_v.distance = distance(data->camera.player_x, data->camera.player_y, next_vert_x, next_vert_y);
			ray_v.distance *= cos(normalize_angle(ray_angle - data->camera.angle));
			ray_v.dir_x = next_vert_x;
			ray_v.dir_y = next_vert_y;
			ray_v.wall = VERTICAL;
			break ;
		}
		else
		{
			next_vert_x += xstep;
			next_vert_y += ystep;
		}
	}
	return ray_v;
}

t_ray	cast_ray(t_data *data, double ray_angle)
{
	t_ray	ray_h;
	t_ray	ray_v;

	ray_h = horizontal_check(data, ray_angle);
	ray_v = vertical_check(data, ray_angle);
	
	
	if (ray_h.distance - ray_v.distance < 0)
		return (ray_h);
	else
		return (ray_v);
	return (ray_v);
}