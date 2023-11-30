/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-hadr < yel-hadr@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 16:29:31 by bbouagou          #+#    #+#             */
/*   Updated: 2023/11/30 21:37:30 by yel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/renderer.h"

int	get_rgba(int r, int g, int b, int a)
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

bool	ft_haswallat(t_data *data, double x, double y, t_ray *ray)
{
	int		map_index_x;
	int		map_index_y;

	map_index_x = floor(x / BLOCK);
	map_index_y = floor(y / BLOCK);
	if (map_index_x < 0 || map_index_x >= (int)data->map.map_width \
		|| map_index_y < 0 || map_index_y >= (int)data->map.map_height)
		return (true);
	if (ray && data->map.map[map_index_y][map_index_x] == 'D')
		ray->is_door = DOOR;
	return (data->map.map[map_index_y][map_index_x] == '1' || \
		data->map.map[map_index_y][map_index_x] == 'D');
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

void	draw_player(t_data *data)
{
	int	x;
	int	y;

	y = (MINIMAP_HEIGHT / 2) - 4;
	while (y < (MINIMAP_HEIGHT / 2) + 4)
	{
		x = (MINIMAP_WIDTH / 2) - 4;
		while (x < (MINIMAP_WIDTH / 2) + 4)
		{
			mlx_put_pixel(data->minimap_img, x, y, \
				data->textures.ceiling_color);
			x++;
		}
		y++;
	}
}
