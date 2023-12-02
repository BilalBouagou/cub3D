/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_v_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 19:41:47 by yel-hadr          #+#    #+#             */
/*   Updated: 2023/12/02 01:08:46 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/renderer.h"

int	calc_to_wall(t_data *data, double angle, t_ray *ray, t_wall wall)
{
	ray->distance = distance(data->camera.player_x, \
		data->camera.player_y, ray->next_x, ray->next_y);
	ray->distance *= cos(normalize_angle(angle - data->camera.angle));
	ray->dir_x = ray->next_x;
	ray->dir_y = ray->next_y;
	ray->wall = wall;
	return (0);
}

t_ray	init_horizontal_check(t_data *data, double ray_angle)
{
	t_ray	ray_h;

	ray_h.north_south = get_direction(ray_angle, true);
	ray_h.east_west = get_direction(ray_angle, false);
	ray_h.distance = INT_MAX;
	ray_h.yintercept = floor(data->camera.player_y / BLOCK) * BLOCK;
	if (ray_h.north_south == SOUTH)
		ray_h.yintercept += BLOCK;
	ray_h.xintercept = data->camera.player_x + (ray_h.yintercept - \
		data->camera.player_y) / tan(ray_angle);
	ray_h.ystep = BLOCK;
	if (ray_h.north_south == NORTH)
		ray_h.ystep *= -1;
	ray_h.xstep = BLOCK / tan(ray_angle);
	if (ray_h.east_west == WEST && ray_h.xstep > 0)
		ray_h.xstep *= -1;
	if (ray_h.east_west == EAST && ray_h.xstep < 0)
		ray_h.xstep *= -1;
	ray_h.next_x = ray_h.xintercept;
	ray_h.next_y = ray_h.yintercept;
	return (ray_h);
}

t_ray	horizontal_check(t_data *data, double ray_angle)
{
	t_ray	ray_h;
	float	x_to_check;
	float	y_to_check;

	ray_h = init_horizontal_check(data, ray_angle);
	while (ray_h.next_x >= 0 && ray_h.next_x <= data->map.map_width * BLOCK \
	&& ray_h.next_y >= 0 && ray_h.next_y <= data->map.map_height * BLOCK)
	{
		x_to_check = ray_h.next_x;
		y_to_check = ray_h.next_y;
		if (ray_h.north_south == NORTH)
			y_to_check += -1;
		if (ft_haswallat(data, x_to_check, y_to_check) && \
			!calc_to_wall(data, ray_angle, &ray_h, HORIZONTAL))
			break ;
		else
		{
			ray_h.next_x += ray_h.xstep;
			ray_h.next_y += ray_h.ystep;
		}
	}
	return (ray_h);
}

t_ray	vertical_check(t_data *data, double ray_angle)
{
	t_ray	ray_v;
	float	x_to_check;
	float	y_to_check;

	ray_v = init_vertical_check(data, ray_angle);
	while (ray_v.next_x >= 0 && ray_v.next_x <= data->map.map_width * BLOCK && \
	ray_v.next_y >= 0 && ray_v.next_y <= data->map.map_height * BLOCK)
	{
		x_to_check = ray_v.next_x;
		if (ray_v.east_west == WEST)
			x_to_check += -1;
		y_to_check = ray_v.next_y;
		if (ft_haswallat(data, x_to_check, y_to_check) && \
		!calc_to_wall(data, ray_angle, &ray_v, VERTICAL))
			break ;
		else
		{
			ray_v.next_x += ray_v.xstep;
			ray_v.next_y += ray_v.ystep;
		}
	}
	return (ray_v);
}

t_ray	cast_ray(t_data *data, double ray_angle)
{
	t_ray	ray_h;
	t_ray	ray_v;

	ray_h = horizontal_check(data, ray_angle);
	ray_v = vertical_check(data, ray_angle);
	if (ray_h.distance - ray_v.distance < 0)
		return (ray_h);
	return (ray_v);
}
