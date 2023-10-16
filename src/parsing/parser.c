/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 08:53:12 by bbouagou          #+#    #+#             */
/*   Updated: 2023/10/17 00:38:22 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

// TODO: refactor code now.

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
}

void	parser(int fd, t_data *data, int map_len)
{
	if (fd == - 1)
		exit(printf(FILEOPENERR));
	if (map_len < 3)
		exit(printf(MAPSIZERR));
	data->map.map = (char **)malloc((map_len + 1) * sizeof(char *));
	read_map(fd, data);
}
