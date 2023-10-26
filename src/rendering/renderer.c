/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 05:38:08 by yel-hadr          #+#    #+#             */
/*   Updated: 2023/10/26 03:58:12 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/renderer.h"

int	get_rgba(int r, int g, int b, int a)
{ 
    return (r << 24 | g << 16 | b << 8 | a);
}

void ft_error(char	*str)
{
	ft_putstr_fd(str, 2);
	exit(EXIT_FAILURE);
}

void	draw_camera(t_data *data, double yc, double xc)
{
	size_t	x;
	size_t	y;
	size_t	xlimit;
	size_t	ylimit;

	x = xc + data->map.block_width / 3;
	y = yc + data->map.block_height / 3;
	xlimit = xc + ((data->map.block_width / 3) * 2);
	ylimit = yc + ((data->map.block_height / 3) * 2);
	while (y < ylimit)
	{
		x = xc + data->map.block_width / 3;
		while (x < xlimit)
		{
			mlx_put_pixel(data->img, x, y, get_rgba(255, 0, 0, 255));
			x++;
		}
		y++;
	}	
}

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
	draw_camera(data, data->camera.player_y, data->camera.player_x);
}

double	detect_collision(t_data *data, double x, double y)
{
	int	i;
	int	j;

	j = ((x) + ((data->map.block_width / 3) * 2)) / data->map.block_width;
	i = ((y) + ((data->map.block_height / 3) * 2)) / data->map.block_height;
	if (data->map.map[i][j] == '1')
		return (0);
	return (2);
}

void	key_hook(mlx_key_data_t key, void *param)
{
	t_data *data = (t_data *)param;
	if (key.key == MLX_KEY_UP)
		data->camera.player_y -= detect_collision(data, data->camera.player_x, data->camera.player_y - 2);
	else if (key.key == MLX_KEY_DOWN)
		data->camera.player_y += detect_collision(data, data->camera.player_x, data->camera.player_y + 2);
	else if (key.key == MLX_KEY_RIGHT)
		data->camera.player_x += detect_collision(data, data->camera.player_x + 2, data->camera.player_y);
	else if (key.key == MLX_KEY_LEFT)
		data->camera.player_x -= detect_collision(data, data->camera.player_x - 2, data->camera.player_y);
	else if (key.key == MLX_KEY_ESCAPE)
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
	mlx_key_hook(data->mlx, key_hook, data);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
}