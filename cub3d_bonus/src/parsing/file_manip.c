/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_manip.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 19:03:09 by bbouagou          #+#    #+#             */
/*   Updated: 2023/12/01 14:37:41 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

void	read_map(int fd, t_data *data)
{
	char	*line;
	int		idx;

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

void	load_map(t_data *data)
{
	size_t	idx;
	size_t	idx2;
	char	**tmp;

	idx = 0;
	while (data->map.map[idx] != NULL
		&& is_map_line(data->map.map[idx]) == false)
		idx++;
	tmp = (char **)malloc((count_map_lines(data, idx) + 1) * sizeof(char *));
	idx2 = 0;
	while (data->map.map[idx] != NULL
		&& is_map_line(data->map.map[idx]) == true)
	{
		tmp[idx2] = ft_strdup(data->map.map[idx]);
		idx2++;
		idx++;
	}
	tmp[idx2] = NULL;
	while (data->map.map[idx] && string_is_whitespace(data->map.map[idx]))
		idx++;
	if (data->map.map[idx])
		exit(printf(FILEFRMTERR));
	p_free_resources(data->map.map);
	data->map.map = tmp;
}

void	get_map_dimensions(t_data *data)
{
	int	idx;
	int	tmp;

	idx = 0;
	tmp = 0;
	data->map.map_height = 0;
	data->map.map_width = 0;
	while (data->map.map[idx])
	{
		tmp = ft_strlen(data->map.map[idx]);
		if (data->map.map_width < tmp)
			data->map.map_width = tmp;
		idx++;
	}
	data->map.map_height = idx;
	if (data->map.map_width > data->map.map_height)
		data->map.ratio = data->map.map_width;
	else
		data->map.ratio = data->map.map_height;
}

void	fill_empty_lines(t_data *data)
{
	size_t	idx;
	size_t	len;
	char	*tmp;

	idx = 0;
	tmp = NULL;
	while (data->map.map[idx])
	{
		len = 0;
		if (ft_strlen(data->map.map[idx]) != (size_t)data->map.map_width)
		{
			len = ft_strlen(data->map.map[idx])
				+ ((size_t)data->map.map_width - ft_strlen(data->map.map[idx]));
			tmp = (char *)ft_calloc(len + 1, sizeof(char));
			ft_strlcpy(tmp, data->map.map[idx],
				ft_strlen(data->map.map[idx]) + 1);
			ft_memset((void *)tmp + ft_strlen(data->map.map[idx]), '0',
				len - ft_strlen(data->map.map[idx]));
			free(data->map.map[idx]);
			data->map.map[idx] = tmp;
		}
		idx++;
	}
}
