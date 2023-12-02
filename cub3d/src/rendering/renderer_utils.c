/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 16:29:31 by bbouagou          #+#    #+#             */
/*   Updated: 2023/12/02 01:07:58 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/renderer.h"

int32_t	get_rgba(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

double	normalize_angle(double angle)
{
	angle = remainder(angle, PI * 2);
	if (angle < 0)
	{
		angle = (2 * PI) + angle;
	}
	return (angle);
}

bool	ft_haswallat(t_data *data, double x, double y)
{
	int32_t		map_index_x;
	int32_t		map_index_y;

	map_index_x = floor(x / BLOCK);
	map_index_y = floor(y / BLOCK);
	if (map_index_x < 0 || map_index_x >= data->map.map_width \
		|| map_index_y < 0 || map_index_y >= data->map.map_height)
		return (true);
	return (data->map.map[map_index_y][map_index_x] == '1');
}

float	distance(float x1, float y1, float x2, float y2)
{
	return (sqrtf((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

void	ft_error(char	*str)
{
	ft_putstr_fd(str, 2);
	exit(EXIT_FAILURE);
}
