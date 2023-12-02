/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 05:38:08 by yel-hadr          #+#    #+#             */
/*   Updated: 2023/12/02 01:04:09 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/renderer.h"

void	initiate_rendering(t_data *data)
{
	raycaster(data);
	mlx_set_cursor_mode(data->mlx, MLX_MOUSE_DISABLED);
	mlx_image_to_window(data->mlx, data->img, 0, 0);
	mlx_loop_hook(data->mlx, key_hook, data);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
}

void	renderer(t_data *data)
{
	data->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D", false);
	if (!data->mlx)
		ft_error((char *)mlx_strerror(mlx_errno));
	data->img = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!data->img)
		ft_error((char *)mlx_strerror(mlx_errno));
	initiate_rendering(data);
}
