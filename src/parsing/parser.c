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
		data->map.map[idx] = ft_strdup(line);
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
	while (data->map.map[i])
	{
		if (is_map_line(data->map.map[i]))
			exit(printf(FILEFRMTERR));
		if (!string_is_whitespace(data->map.map[i]))
		{
			if (string_has_valid_identifier(data->map.map[i]))
				load_component_to_struct(data, data->map.map[i]);
		}
	}
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
	// check_borders(data, map_len);
}
