/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouvement_hook.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 23:31:31 by bbouagou          #+#    #+#             */
/*   Updated: 2023/12/01 16:02:25 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/renderer.h"

bool	haswall(t_data *data, float d_x, float d_y)
{
	float	p_x;
	float	p_y;

	p_x = data->camera.player_x;
	p_y = data->camera.player_y;
	if (!ft_haswallat(data, p_x + d_x, p_y + d_y, NULL))
	{
		if (!ft_haswallat(data, p_x + (d_x * 4), p_y, NULL) && \
			!ft_haswallat(data, p_x, p_y +(d_y * 4), NULL))
		{
			return (true);
		}
	}
	return (false);
}

void	move_player(t_data *data, float d_x, float d_y)
{
	data->camera.player_x += d_x;
	data->camera.player_y += d_y;
}

void	has_doorat(t_data *data, double x, double y)
{
	int		map_index_x;
	int		map_index_y;

	x += data->camera.dir_x * 32;
	y += data->camera.dir_y * 32;
	map_index_x = floor(x / BLOCK);
	map_index_y = floor(y / BLOCK);
	if (map_index_x < 0 || map_index_x >= (int)data->map.map_width \
		|| map_index_y < 0 || map_index_y >= (int)data->map.map_height)
		return ;
	if (data->map.map[map_index_y][map_index_x] == 'O')
		data->map.map[map_index_y][map_index_x] = 'D';
	else if (data->map.map[map_index_y][map_index_x] == 'D')
		data->map.map[map_index_y][map_index_x] = 'O';
}

void	door_hook(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keydata.key == MLX_KEY_SPACE && keydata.action == MLX_PRESS)
	{
		has_doorat(data, data->camera.player_x, data->camera.player_y);
	}
}

void	key_hook(void *param)
{
	t_data	*data;
	float	d_x;
	float	d_y;

	data = (t_data *)param;
	d_x = data->camera.dir_x;
	d_y = data->camera.dir_y;
	if ((mlx_is_key_down(data->mlx, MLX_KEY_UP) || mlx_is_key_down(data->mlx, \
	MLX_KEY_W)) && haswall(data, d_x, d_y))
		move_player(data, d_x, d_y);
	else if ((mlx_is_key_down(data->mlx, MLX_KEY_DOWN) || \
	mlx_is_key_down(data->mlx, MLX_KEY_S)) && haswall(data, -d_x, -d_y))
		move_player(data, -d_x, -d_y);
	else if ((mlx_is_key_down(data->mlx, MLX_KEY_A)) && \
		haswall(data, d_y, -d_x))
		move_player(data, d_y, -d_x);
	else if (mlx_is_key_down(data->mlx, MLX_KEY_D) && \
		haswall(data, -d_y, d_x))
		move_player(data, -d_y, d_x);
	else if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		exit(EXIT_SUCCESS);
	raycaster(data);
}
