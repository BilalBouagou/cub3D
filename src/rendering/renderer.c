/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-hadr < yel-hadr@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 05:38:08 by yel-hadr          #+#    #+#             */
/*   Updated: 2023/11/02 00:53:01 by yel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/renderer.h"

void	fill_img(t_data *data, uint32_t x, uint32_t y, uint32_t color)
{
	size_t	xm;
	size_t	ym;
	size_t	ylimit;
	size_t	xlimit;
	(void)color;

	ym = y * BLOCK + 1;
	ylimit = ((y * BLOCK) + BLOCK);
	xlimit = ((x * BLOCK) + BLOCK);
	while (ym < ylimit)
	{
		xm = x * BLOCK + 1; 
		while (xm < xlimit)
		{
			if (xm < xlimit - 1  && ym < ylimit -1)
				mlx_put_pixel(data->img, xm, ym, color);
			xm++;
		}
		ym++;
	}
}

float	distance(float x1, float y1, float x2, float y2)
{
	return (sqrtf((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

t_direc get_direction(t_data *data, double ray_angle, bool flag)
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
		else if ((ray_angle > 3 * PI / 2 && ray_angle < 2 * PI) || (ray_angle > 0 && ray_angle < PI / 2))
			return (EAST);
	}
	return (NO_DIRECTION);
}

bool	ft_haswallat(t_data *data, double x, double y)
{
	int		map_index_x;
	int		map_index_y;

	map_index_x = floor(x / BLOCK);
	map_index_y = floor(y / BLOCK);
	if (map_index_x < 0 || map_index_x >= data->map.map_width || map_index_y < 0 || map_index_y >= data->map.map_height)
		return (true);
	return (data->map.map[map_index_y][map_index_x] == '1');
}

t_ray	cast_ray(t_data *data, double ray_angle)
{
	t_ray	ray_h;
	t_ray	ray_v;
	double	yintercept, xintercept;
	double	xstep, ystep;

	// horizontal ray-grid intersection code
	ray_h.north_south = get_direction(data, ray_angle, true);
	ray_h.east_west = get_direction(data, ray_angle, false);
	ray_h.distance = INT_MAX;

	// find the y-coordinat and the x-coordinat of the first horizontal grid line we are going to hit
	yintercept = floor(data->camera.player_y / BLOCK) * BLOCK;
	yintercept += ray_h.north_south == SOUTH ? BLOCK : 0;
	xintercept = data->camera.player_x + (yintercept - data->camera.player_y) / tan(ray_angle);

	// calculate the increment xstep and ystep
	ystep = BLOCK;
	ystep *= ray_h.north_south == NORTH ? -1 : 1;
	xstep = BLOCK / tan(ray_angle);
	xstep *= (ray_h.east_west == WEST && xstep > 0) ? -1 : 1;
	xstep *= (ray_h.east_west == EAST && xstep < 0) ? -1 : 1;

	// find the next horizontal intersection
	double next_horz_x = xintercept;
	double next_horz_y = yintercept;
	if (ray_h.north_south == NORTH)
		next_horz_y--;
	while (next_horz_x >= 0 && next_horz_x <= data->map.map_width * BLOCK && next_horz_y >= 0 && next_horz_y <= data->map.map_height * BLOCK)
	{
		if (ft_haswallat(data, next_horz_x, next_horz_y))
		{
			ray_h.distance = distance(data->camera.player_x, data->camera.player_y, next_horz_x, next_horz_y);
			ray_h.dir_x = next_horz_x;
			ray_h.dir_y = next_horz_y;
			ray_h.wall = HORIZONTAL;
			break ;
		}
		else
		{
			next_horz_x += xstep;
			next_horz_y += ystep;
		}
	}

	// vertical ray-grid intersection code

	ray_v.north_south = get_direction(data, ray_angle, true);
	ray_v.east_west = get_direction(data, ray_angle, false);
	ray_v.distance = INT_MAX;

	// find the x-coordinat and the y-coordinat of the first vertical grid line we are going to hit
	xintercept = floor(data->camera.player_x / BLOCK) * BLOCK;
	xintercept += ray_v.east_west == EAST ? BLOCK : 0;
	yintercept = data->camera.player_y + (xintercept - data->camera.player_x) * tan(ray_angle);

	// calculate the increment xstep and ystep
	xstep = BLOCK;
	xstep *= ray_v.east_west == WEST ? -1 : 1;
	ystep = BLOCK * tan(ray_angle);
	ystep *= (ray_v.north_south == NORTH && ystep > 0) ? -1 : 1;
	ystep *= (ray_v.north_south == SOUTH && ystep < 0) ? -1 : 1;

	// find the next vertical intersection
	double next_vert_x = xintercept;
	double next_vert_y = yintercept;
	if (ray_v.east_west == WEST)
		next_vert_x--;
	while (next_vert_x >= 0 && next_vert_x <= data->map.map_width * BLOCK && next_vert_y >= 0 && next_vert_y <= data->map.map_height * BLOCK)
	{
		if (ft_haswallat(data, next_vert_x, next_vert_y))
		{
			ray_v.distance = distance(data->camera.player_x, data->camera.player_y, next_vert_x, next_vert_y);
			ray_v.dir_x = next_vert_x;
			ray_v.dir_y = next_vert_y;
			ray_v.wall = VERTICAL;
			break ;
		}
		else
		{
			next_vert_x += xstep;
			next_vert_y += ystep;
		}
	}
	if (ray_h.distance < ray_v.distance)
		return (ray_h);
	else
		return (ray_v);
}

double normalize_angle(double angle)
{
	angle = remainder(angle, 2 * PI);
	if (angle < 0)
		angle += 2 * PI;
	return (angle);
}

void	ft_3d_projection(t_data *data, t_ray ray, int x)
{
	double wall_strip_height;
	int32_t wall_top;
	int32_t wall_bottom;

	wall_strip_height = (BLOCK / ray.distance) * DISTANCE_PROJ_PLANE;
	wall_top = (WINDOW_HEIGHT / 2) - (wall_strip_height / 2);
	wall_bottom = (WINDOW_HEIGHT / 2) + (wall_strip_height / 2);

	draw_line(data, x, wall_top, x, wall_bottom, get_rgba(255, 255, 255, 255));
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
		ray_cast.distance *= cos(ray_angle - data->camera.angle);
		if (ray_cast.wall != NO_WALL)
			ft_3d_projection(data, ray_cast, ray);
		ray_angle += (double)DEGRE * (double)FOV_ANGLE / (double)WINDOW_WIDTH;
		ray_angle = normalize_angle(ray_angle);
		ray++;
	}
}

void	minimap(t_data *data)
{
	// size_t	i;
	// size_t	j;

	// i = 0;
	// while (data->map.map[i])
	// {
	// 	j = 0;
	// 	while(data->map.map[i][j])
	// 	{
	// 		if (data->map.map[i][j] == '1')
	// 			fill_img(data, j, i, get_rgba(100, 150, 50, 255));
	// 		else
	// 			fill_img(data, j, i, get_rgba(0, 0, 0, 255));
	// 		j++;
	// 	}
	// 	i++;
	// }
	draw_player(data);
	ft_draw_rays(data);
}

void	key_hook(void *param)
{
	t_data *data = (t_data *)param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_UP))
	{
		
		if (data->map.map[(int)(data->camera.player_y + data->camera.dir_y) / BLOCK][(int)(data->camera.player_x + data->camera.dir_x) / BLOCK] != '1')
		{
			data->camera.player_x += data->camera.dir_x;
			data->camera.player_y += data->camera.dir_y;
		}
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_DOWN))
	{
		if (data->map.map[(int)(data->camera.player_y - data->camera.dir_y) / BLOCK][(int)(data->camera.player_x - data->camera.dir_x) / BLOCK] != '1')
		{
			data->camera.player_x -= data->camera.dir_x;
			data->camera.player_y -= data->camera.dir_y;
		}
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
	{
		data->camera.angle += 0.01;
		if (data->camera.angle > 2 * PI)
			data->camera.angle -= 2 * PI;
		data->camera.dir_x = cos(data->camera.angle) * 4;
		data->camera.dir_y = sin(data->camera.angle) * 4;
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
	{
		data->camera.angle -= 0.01;
		if (data->camera.angle < 0)
			data->camera.angle += 2 * PI;
		data->camera.dir_x = cos(data->camera.angle) * 4;
		data->camera.dir_y = sin(data->camera.angle) * 4;
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