/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 05:38:08 by yel-hadr          #+#    #+#             */
/*   Updated: 2023/12/01 00:29:14 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/renderer.h"

void	cursor_hook(double xpos, double ypos, void *param)
{
	t_data		*data;
	static int	oldxpos;

	(void)ypos;
	data = (t_data *)param;
	if (oldxpos == 0)
		oldxpos = xpos;
	if (oldxpos < xpos)
	{
		data->camera.angle += 0.02;
		if (data->camera.angle > 2 * PI)
			data->camera.angle -= 2 * PI;
		data->camera.dir_x = cos(data->camera.angle) * SPEED;
		data->camera.dir_y = sin(data->camera.angle) * SPEED;
	}
	else if (oldxpos > xpos)
	{
		data->camera.angle -= 0.02;
		if (data->camera.angle < 0)
			data->camera.angle += 2 * PI;
		data->camera.dir_x = cos(data->camera.angle) * SPEED;
		data->camera.dir_y = sin(data->camera.angle) * SPEED;
	}
	oldxpos = xpos;
}

void	mouse_hook(mouse_key_t button, action_t action,
	modifier_key_t mods, void *param)
{
	t_data	*data;

	(void)mods;
	if (button == MLX_MOUSE_BUTTON_LEFT && action == MLX_PRESS)
	{
		data = (t_data *)param;
		if (data->anim_count == 0)
			data->anim_count = 1;
	}
}

void	initiate_rendering(t_data *data)
{
	ft_memset(data->minimap_img->pixels, 255,
		MINIMAP_WIDTH * MINIMAP_HEIGHT * sizeof(int32_t));
	raycaster(data);
	mlx_set_cursor_mode(data->mlx, MLX_MOUSE_DISABLED);
	mlx_image_to_window(data->mlx, data->img, 0, 0);
	mlx_image_to_window(data->mlx, data->gun_img,
		WINDOW_WIDTH / 3 + WINDOW_WIDTH / 18, 408);
	mlx_image_to_window(data->mlx, data->status_bar_img, 0, 0);
	mlx_image_to_window(data->mlx, data->minimap_img, 132, 0);
	mlx_loop_hook(data->mlx, key_hook, data);
	mlx_cursor_hook(data->mlx, cursor_hook, data);
	mlx_mouse_hook(data->mlx, mouse_hook, data);
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
	data->gun_img = mlx_texture_to_image(data->mlx, &data->gun_1->texture);
	if (!data->gun_img)
		ft_error((char *)mlx_strerror(mlx_errno));
	data->status_bar_img = mlx_texture_to_image(data->mlx, data->status_bar);
	if (!data->status_bar_img)
		ft_error((char *)mlx_strerror(mlx_errno));
	data->minimap_img = mlx_new_image(data->mlx, MINIMAP_WIDTH, MINIMAP_HEIGHT);
	if (!data->minimap_img)
		ft_error((char *)mlx_strerror(mlx_errno));
	initiate_rendering(data);
}
