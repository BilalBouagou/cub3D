/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouvement_hook.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 23:31:31 by bbouagou          #+#    #+#             */
/*   Updated: 2023/12/02 01:10:03 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/renderer.h"

bool	haswall(t_data *data, float d_x, float d_y)
{
	float	p_x;
	float	p_y;

	p_x = data->camera.player_x;
	p_y = data->camera.player_y;
	if (!ft_haswallat(data, p_x + d_x, p_y + d_y))
	{
		if (!ft_haswallat(data, p_x + (d_x * 4), p_y) && \
			!ft_haswallat(data, p_x, p_y +(d_y * 4)))
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

void	rotate_view(t_data *data, bool flag)
{
	if (flag)
	{
		data->camera.angle += 0.03;
		if (data->camera.angle > 2 * PI)
			data->camera.angle -= 2 * PI;
		data->camera.dir_x = cos(data->camera.angle) * SPEED;
		data->camera.dir_y = sin(data->camera.angle) * SPEED;
	}
	else
	{
		data->camera.angle -= 0.03;
		if (data->camera.angle < 0)
			data->camera.angle += 2 * PI;
		data->camera.dir_x = cos(data->camera.angle) * SPEED;
		data->camera.dir_y = sin(data->camera.angle) * SPEED;
	}
}

void	key_hook(void *param)
{
	t_data	*data;
	float	d_xy[2];

	data = (t_data *)param;
	d_xy[0] = data->camera.dir_x;
	d_xy[1] = data->camera.dir_y;
	if ((mlx_is_key_down(data->mlx, MLX_KEY_UP) || mlx_is_key_down(data->mlx, \
	MLX_KEY_W)) && haswall(data, d_xy[0], d_xy[1]))
		move_player(data, d_xy[0], d_xy[1]);
	else if ((mlx_is_key_down(data->mlx, MLX_KEY_DOWN) || \
	mlx_is_key_down(data->mlx, MLX_KEY_S)) && haswall(data, -d_xy[0], -d_xy[1]))
		move_player(data, -d_xy[0], -d_xy[1]);
	else if ((mlx_is_key_down(data->mlx, MLX_KEY_A)) && \
		haswall(data, d_xy[1], -d_xy[0]))
		move_player(data, d_xy[1], -d_xy[0]);
	else if (mlx_is_key_down(data->mlx, MLX_KEY_D) && \
		haswall(data, -d_xy[1], d_xy[0]))
		move_player(data, -d_xy[1], d_xy[0]);
	else if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		rotate_view(data, true);
	else if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		rotate_view(data, false);
	else if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		exit(EXIT_SUCCESS);
	raycaster(data);
}
