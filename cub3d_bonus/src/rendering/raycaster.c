/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 23:40:37 by bbouagou          #+#    #+#             */
/*   Updated: 2023/12/01 22:23:10 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/renderer.h"

t_direc	get_direction(double ray_angle, bool flag)
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
		else if ((ray_angle > 3 * PI / 2 && ray_angle < 2 * PI) \
		|| (ray_angle > 0 && ray_angle < PI / 2))
			return (EAST);
	}
	return (NO_DIRECTION);
}

void	raycaster(t_data *data)
{
	double	ray_angle;
	int32_t	ray;
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
	gun_anim(data);
	minimap(data);
}
