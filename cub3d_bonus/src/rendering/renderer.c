/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-hadr < yel-hadr@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 05:38:08 by yel-hadr          #+#    #+#             */
/*   Updated: 2023/11/30 23:24:39 by yel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/renderer.h"

void	gun_anim(t_data *data);
void	ft_minimap(t_data *data);

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

void	ft_draw_rays(t_data *data)
{
	double	ray_angle;
	int		ray;
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
}

void	minimap(t_data *data)
{
	ft_draw_rays(data);
	gun_anim(data);
}

int	move_player(t_data *data, float d_x, float d_y)
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
			return (1);
		}
	}
	return (0);
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
	MLX_KEY_W)) && move_player(data, d_x, d_y))
	{
		data->camera.player_x += d_x;
		data->camera.player_y += d_y;
	}
	else if ((mlx_is_key_down(data->mlx, MLX_KEY_DOWN) || \
	mlx_is_key_down(data->mlx, MLX_KEY_S)) && move_player(data, -d_x, -d_y))
	{
		data->camera.player_x -= d_x;
		data->camera.player_y -= d_y;
	}
	else if ((mlx_is_key_down(data->mlx, MLX_KEY_A)) && \
		move_player(data, d_y, -d_x))
	{
		data->camera.player_x += d_y;
		data->camera.player_y -= d_x;
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_D) && \
		move_player(data, -d_y, d_x))
	{
		data->camera.player_x -= d_y;
		data->camera.player_y += d_x;
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
	{
		data->camera.angle += 0.01;
		if (data->camera.angle > 2 * PI)
			data->camera.angle -= 2 * PI;
		data->camera.dir_x = cos(data->camera.angle) * SPEED;
		data->camera.dir_y = sin(data->camera.angle) * SPEED;
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
	{
		data->camera.angle -= 0.01;
		if (data->camera.angle < 0)
			data->camera.angle += 2 * PI;
		data->camera.dir_x = cos(data->camera.angle) * SPEED;
		data->camera.dir_y = sin(data->camera.angle) * SPEED;
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		exit(EXIT_SUCCESS);
	minimap(data);
}

void	cursor_hook(double xpos, double ypos, void *param)
{
	t_data	*data = (t_data *)param;

	(void)ypos;
	static int oldxpos;
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

void	gun_anim(t_data *data)
{
	if (data->anim_count == 0)
	{
		mlx_delete_image(data->mlx, data->gun_img);
		data->gun_img = mlx_texture_to_image(data->mlx, &data->gun_1->texture);
		mlx_image_to_window(data->mlx, data->gun_img, WINDOW_WIDTH / 3 + WINDOW_WIDTH / 18, 408);
	}
	else if (data->anim_count < 10)
	{
		mlx_delete_image(data->mlx, data->gun_img);
		data->gun_img = mlx_texture_to_image(data->mlx, &data->gun_2->texture);
		mlx_image_to_window(data->mlx, data->gun_img, WINDOW_WIDTH / 3 + WINDOW_WIDTH / 18, 408);
		data->anim_count++;
	}
	else if (data->anim_count < 20)
	{
		mlx_delete_image(data->mlx, data->gun_img);
		data->gun_img = mlx_texture_to_image(data->mlx, &data->gun_3->texture);
		mlx_image_to_window(data->mlx, data->gun_img, WINDOW_WIDTH / 3 + WINDOW_WIDTH / 18, 408);
		data->anim_count++;
	}
	else if (data->anim_count < 30)
	{
		mlx_delete_image(data->mlx, data->gun_img);
		data->gun_img = mlx_texture_to_image(data->mlx, &data->gun_4->texture);
		mlx_image_to_window(data->mlx, data->gun_img, WINDOW_WIDTH / 3 + WINDOW_WIDTH / 18, 408);
		data->anim_count++;
	}
	else if (data->anim_count == 30)
	{
		mlx_delete_image(data->mlx, data->gun_img);
		data->gun_img = mlx_texture_to_image(data->mlx, &data->gun_1->texture);
		mlx_image_to_window(data->mlx, data->gun_img, WINDOW_WIDTH / 3 + WINDOW_WIDTH / 18, 408);
		data->anim_count = 0;
	}
	else
		data->anim_count++;
}

void	mouse_hook(mouse_key_t button, action_t action, modifier_key_t mods, void* param)
{
	(void)mods;
	if (button == MLX_MOUSE_BUTTON_LEFT && action == MLX_PRESS)
	{
		t_data *data = (t_data *)param;
		if (data->anim_count == 0)
			data->anim_count = 1;
	}
}

void	ft_minimap(t_data *data)
{
	int	x;
	int	y;
	int	i;
	int	j;
	y = data->camera.player_y - (MINIMAP_HEIGHT / 2);
	i = 0;
	while(i < MINIMAP_HEIGHT)
	{
		x = data->camera.player_x - (MINIMAP_WIDTH / 2);
		j = 0;
		while (j < MINIMAP_WIDTH)
		{
			if (x < 0 || y < 0)
			{
				mlx_put_pixel(data->minimap_img, j, i, get_rgba(0, 0, 0, 255));
			}
			else
			{
				if (data->map.map[y / BLOCK][x / BLOCK] == '1')
					mlx_put_pixel(data->minimap_img, j, i, get_rgba(255, 255, 255, 255));
				else
					mlx_put_pixel(data->minimap_img, j, i, get_rgba(173, 216, 230, 255));
			}
			x++;
			j++;
		}
		y++;
		i++;
	}
	draw_player(data);
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
	data->status_bar_img = mlx_texture_to_image(data->mlx, data->status_bar);
	data->minimap_img = mlx_new_image(data->mlx, MINIMAP_WIDTH, MINIMAP_HEIGHT);
	ft_memset(data->minimap_img->pixels, 255, MINIMAP_WIDTH * MINIMAP_HEIGHT * sizeof(int32_t));
	minimap(data);
	mlx_set_cursor_mode(data->mlx, MLX_MOUSE_DISABLED);
	mlx_image_to_window(data->mlx, data->img, 0, 0);
	mlx_image_to_window(data->mlx, data->gun_img, WINDOW_WIDTH / 3 + WINDOW_WIDTH / 18, 408);
	mlx_image_to_window(data->mlx, data->status_bar_img, 0, 0);
	mlx_image_to_window(data->mlx, data->minimap_img, 132, 0);
	mlx_loop_hook(data->mlx, key_hook, data);
	mlx_cursor_hook(data->mlx, cursor_hook, data);
	mlx_mouse_hook(data->mlx, mouse_hook, data);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
}
