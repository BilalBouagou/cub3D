/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-hadr < yel-hadr@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 05:38:08 by yel-hadr          #+#    #+#             */
/*   Updated: 2023/10/29 04:52:02 by yel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/renderer.h"

void	fill_img(t_data *data, uint32_t x, uint32_t y, int color)
{
	size_t	xm;
	size_t	ym;
	size_t	ylimit;
	size_t	xlimit;
	(void)color;

	ym = y * data->map.block_height;
	ylimit = ((y * data->map.block_height) + data->map.block_height);
	xlimit = ((x * data->map.block_width) + data->map.block_width);
	while (ym < ylimit)
	{
		xm = x * data->map.block_width; 
		while (xm < xlimit)
		{
			if (xm < xlimit - 2  && ym < ylimit -2)
			{
				mlx_put_pixel(data->img, xm, ym, color);
			}
			else
				mlx_put_pixel(data->img, xm, ym, 0);
			xm++;
		}
		ym++;
	}

}

void	ft_draw_rays(t_data *data)
{
	int r;
	int mx;
	int my;
	int mp;
	int dof;
	float rx;
	float ry;
	float ra;
	float xo;
	float yo;
	
	ra = data->camera.angle;
	r = 0;

	while(r < 1)
	{
		dof = 0;
		float atan = -1/tan(ra);
		if (ra > PI)
		{
			ry = (((int)data->camera.player_y >> 5) << 5) - 0.0001;
			rx = (data->camera.player_y - ry) * atan + data->camera.player_x;
			yo = -32;
			xo = -yo * atan;
		}
		if (ra < PI)
		{
			ry = (((int)data->camera.player_y >> 5) << 5) + 32;
			rx = (data->camera.player_y - ry) * atan + data->camera.player_x;
			yo = 32;
			xo = -yo * atan;
		}
		if (ra == 0 || ra == PI)
		{
			rx = data->camera.player_x;
			ry = data->camera.player_y;
			dof = 8;
		}
		while (dof < 8)
		{
			mx = (int)(rx) >> 5;
			my = (int)(ry) >> 5;
			if (mx <0 || mx > (int)data->map.map_width || my < 0 || my > (int)data->map.map_height)
			{
				break;
			}
			mp = my * data->map.map_width + mx;
			if (mp > 0 && mp < (int)(data->map.map_width * data->map.map_height) && data->map.map[my][mx] == '1')
			{
				printf ("dof = %d\n", dof);
				dof = 8;
			}
			else
			{
				printf ("dof = %d\n", dof);
				rx += xo;
				ry += yo;
				dof++;
			}
			mp = my * data->map.map_width + mx;
			
		}

		dof = 0;
		
		draw_line(data, data->camera.player_x, data->camera.player_y, rx, ry, get_rgba(255, 222, 0, 255));
		r++;
	}
}

void	minimap(t_data *data)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (data->map.map[i])
	{
		j = 0;
		while(data->map.map[i][j])
		{
			if (data->map.map[i][j] == '1')
				fill_img(data, j, i, get_rgba(100, 150, 50, 255));
			else
				fill_img(data, j, i, get_rgba(0, 0, 0, 255));
			j++;
		}
		i++;
	}
	draw_player(data);
	draw_line(data, data->camera.player_x, data->camera.player_y, data->camera.player_x + data->camera.dir_x, data->camera.player_y + data->camera.dir_y, get_rgba(255, 0, 0, 255));
	ft_draw_rays(data);
}

void	key_hook(void *param)
{
	t_data *data = (t_data *)param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_UP))
	{
		data->camera.player_x += data->camera.dir_x;
		data->camera.player_y += data->camera.dir_y;
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_DOWN))
	{
		data->camera.player_x -= data->camera.dir_x;
		data->camera.player_y -= data->camera.dir_y;
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
	{
		data->camera.angle -= 0.1;
		if (data->camera.angle < 0)
			data->camera.angle = 2 * PI;
		data->camera.dir_x = cos(data->camera.angle) * 10;
		data->camera.dir_y = sin(data->camera.angle) * 10;
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
	{
		data->camera.angle += 0.1;
		if (data->camera.angle > 2 * PI)
			data->camera.angle = 0;
		data->camera.dir_x = cos(data->camera.angle) * 10;
		data->camera.dir_y = sin(data->camera.angle) * 10;
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		exit(EXIT_SUCCESS);
	mlx_delete_image(data->mlx, data->img);
	data->img = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	mlx_image_to_window(data->mlx, data->img, 0, 0);
	minimap(data);
}

void	renderer(t_data *data)
{
	data->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D", false);
	if (!data->mlx)
		ft_error((char *)mlx_strerror(mlx_errno));
	data->img = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!data->img)
		ft_error((char *)mlx_strerror(mlx_errno));
	minimap(data);
	mlx_image_to_window(data->mlx, data->img, 0, 0);
	mlx_loop_hook(data->mlx, key_hook, data);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
}