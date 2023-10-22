/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 08:53:12 by bbouagou          #+#    #+#             */
/*   Updated: 2023/10/20 08:28:03 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

void	read_map(int fd, t_data *data)
{
    char    *line;
    int     idx;

    line = get_next_line(fd);
    idx = 0;
    while (line)
    {
		data->map.map[idx] = ft_strtrim(line, "\n");
		free (line);
		line = get_next_line(fd);
		idx++;
    }
	data->map.map[idx] = NULL;
	close(fd);
}

void	load_map_textures(t_data *data)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (data->map.map[i])
	{
		if (is_map_line(data->map.map[i]))
			exit(printf(FILEFRMTERR));
		if (string_is_whitespace(data->map.map[i]) != true)
		{
			if (string_has_valid_identifier(data->map.map[i]))
			{
				load_component_to_struct(data, data->map.map[i]);
				j++;
			}
			else
				exit(printf(FILEFRMTERR));
			if (j == 6)
				return;
		}
		i++;
	}
	exit(printf(FILEFRMTERR));
}

void	check_textures_path(t_data *data)
{
	int	fd;

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

void	load_map(t_data *data)
{
	size_t	idx;
	size_t	idx2;
	char	**tmp;

	idx = 0;
	while (data->map.map[idx] != NULL && is_map_line(data->map.map[idx]) == false)
		idx++;
	tmp = (char **)malloc((count_map_lines(data, idx) + 1) * sizeof(char *));
	idx2 = 0;
	while (data->map.map[idx] != NULL && is_map_line(data->map.map[idx]) == true)
	{
		tmp[idx2] = ft_strdup(data->map.map[idx]);
		idx2++;
		idx++;
	}
	tmp[idx2] = NULL;
	if (data->map.map[idx])
		exit(printf(FILEFRMTERR));
	p_free_resources(data->map.map);
	data->map.map = tmp;
}

void	check_borders(t_data *data, int map_len)
{
	/*
		imma code it later
	*/
}

void	parser(int fd, t_data *data, int map_len)
{
	if (fd == - 1)
		exit(printf(FILEOPENERR));
	if (map_len < 3)
		exit(printf(MAPSIZERR));
	data->map.map = (char **)malloc((map_len + 1) * sizeof(char *));
	read_map(fd, data);
	load_map_textures(data);
	check_textures_path(data);
	load_map(data);
	// check_borders(data, map_len);
}
