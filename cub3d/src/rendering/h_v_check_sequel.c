/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_v_check_sequel.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 00:53:35 by bbouagou          #+#    #+#             */
/*   Updated: 2023/12/02 01:08:52 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/renderer.h"

t_ray	init_vertical_check(t_data *data, double ray_angle)
{
	t_ray	ray_v;

	ray_v.north_south = get_direction(ray_angle, true);
	ray_v.east_west = get_direction(ray_angle, false);
	ray_v.distance = INT_MAX;
	ray_v.xintercept = floor(data->camera.player_x / BLOCK) * BLOCK;
	if (ray_v.east_west == EAST)
		ray_v.xintercept += BLOCK;
	ray_v.yintercept = data->camera.player_y + (ray_v.xintercept - \
		data->camera.player_x) * tan(ray_angle);
	ray_v.xstep = BLOCK;
	if (ray_v.east_west == WEST)
		ray_v.xstep *= -1;
	ray_v.ystep = BLOCK * tan(ray_angle);
	if (ray_v.north_south == NORTH && ray_v. ystep > 0)
		ray_v.ystep *= -1;
	if (ray_v.north_south == SOUTH && ray_v.ystep < 0)
		ray_v.ystep *= -1;
	ray_v.next_x = ray_v.xintercept;
	ray_v.next_y = ray_v.yintercept;
	return (ray_v);
}
