/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 08:53:12 by bbouagou          #+#    #+#             */
/*   Updated: 2023/12/02 01:06:24 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

void	load_map_textures(t_data *data)
{
	int32_t	i;
	int32_t	id_count;

	i = 0;
	id_count = 0;
	while (data->map.map[i])
	{
		if (string_is_whitespace(data->map.map[i]) != true)
		{
			if (id_count == 6 && is_map_line(data->map.map[i]))
				break ;
			if (string_has_valid_identifier(data->map.map[i]))
			{
				load_component_to_struct(data, data->map.map[i]);
				id_count++;
			}
			else
				exit(printf(FILEFRMTERR));
		}
		i++;
	}
}

void	check_textures_path(t_data *data)
{
	int32_t	fd;

	fd = open(data->textures.north_texture, O_RDONLY);
	if (fd == -1)
		exit(printf(NOTXTERR));
	close(fd);
	fd = open(data->textures.south_texture, O_RDONLY);
	if (fd == -1)
		exit(printf(SOTXTERR));
	close(fd);
	fd = open(data->textures.west_texture, O_RDONLY);
	if (fd == -1)
		exit(printf(WETXTERR));
	close(fd);
	fd = open(data->textures.east_texture, O_RDONLY);
	if (fd == -1)
		exit(printf(EATXTERR));
	close(fd);
}

void	initialise_variables(t_data *data)
{
	data->map.block_width = BLOCK;
	data->map.block_height = BLOCK;
	data->camera.player_x = data->camera.player_x
		* data->map.block_width + data->map.block_width / 2;
	data->camera.player_y = data->camera.player_y
		* data->map.block_height + data->map.block_height / 2;
	data->camera.dir_x = cos(data->camera.angle) * SPEED;
	data->camera.dir_y = sin(data->camera.angle) * SPEED;
	data->north = mlx_load_png(data->textures.north_texture);
	data->south = mlx_load_png(data->textures.south_texture);
	data->east = mlx_load_png(data->textures.east_texture);
	data->west = mlx_load_png(data->textures.west_texture);
	data->distance_proj_plane = ((WINDOW_WIDTH / 2)
			/ tan(FOV_ANGLE / 2 * DEGRE));
}

void	parser(int32_t fd, t_data *data, int32_t map_len)
{
	if (fd == -1)
		exit(printf(FILEOPENERR));
	if (map_len < 3)
		exit(printf(MAPSIZERR));
	data->map.map = (char **)malloc((map_len + 1) * sizeof(char *));
	read_map(fd, data);
	load_map_textures(data);
	check_textures_path(data);
	load_map(data);
	check_map_components(data);
	get_map_dimensions(data);
	initialise_variables(data);
	fill_empty_lines(data);
	check_map_borders(data);
}