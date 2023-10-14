/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 08:53:12 by bbouagou          #+#    #+#             */
/*   Updated: 2023/08/30 14:56:43 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

// refactor code later

char	**read_map(int fd, char **map)
{
	char	**tmp;
	char	*line;
	size_t	itr;
	size_t	idx;

	itr = 1;
	map = (char **)malloc(itr * sizeof(char *));
	map[0] = NULL;
	line = get_next_line(fd);
	while (line)
	{
		idx = -1;
		itr++;
		tmp = map;
		map = (char **)malloc(itr * sizeof(char *));
		while (tmp && tmp[++idx])
		{
			map[idx] = (char *)malloc(ft_len(tmp[idx]) + 1);
			ft_strlcpy(map[idx], tmp[idx], ft_len(tmp[idx]) + 1);
		}
		map[idx] = (char *)malloc(ft_len(line) + 1);
		ft_strlcpy(map[idx], (const char *)line, ft_len(line) + 1);
		map[++idx] = NULL;
		p_free_resources(tmp);
		free(line);
		line = get_next_line(fd);
	}
	return (map);
}

// holy fuck need to be normed asap
// seems to be working

size_t	load_textures(t_data *data)
{
	char	**segment;
	size_t	itr;
	size_t	count;

	itr = 0;
	count = 0;
	segment = NULL;
	while (data->map.map && data->map.map[itr] && !ft_strcmp(data->map.map[itr], "\n"))
		itr++;
	while (data->map.map && data->map.map[itr])
	{
		segment = ft_split(data->map.map[itr], ' ');
		if (segment && segment[0] && ft_strcmp(segment[0], "NO") && ft_strcmp(segment[0], "SO") && ft_strcmp(segment[0], "WE") && ft_strcmp(segment[0], "EA") && ft_strcmp(segment[0], "F") && ft_strcmp(segment[0], "C"))
		{
			printf("Unrecognized ID found in file.\n");
			exit(EXIT_SUCCESS);
		}
		else if (segment && segment[0] && !segment[1])
		{
			printf("ID missing corresponding info.\n");
			exit(EXIT_SUCCESS);
		}
		else if (array_len(segment) >= 2)
		{
			if (!ft_strcmp(segment[0], "NO"))
			{
				data->textures.north_texture = (char *)malloc(ft_strlen(segment[1] + 1));
				ft_strlcpy(data->textures.north_texture, ft_strtrim(segment[1], "\n"), ft_strlen(segment[1]) + 1);
			}
			else if (!ft_strcmp(segment[0], "SO"))
			{
				data->textures.south_texture = (char *)malloc(ft_strlen(segment[1] + 1));
				ft_strlcpy(data->textures.south_texture, ft_strtrim(segment[1], "\n"), ft_strlen(segment[1]) + 1);
			}
			else if (!ft_strcmp(segment[0], "WE"))
			{
				data->textures.west_texture = (char *)malloc(ft_strlen(segment[1] + 1));
				ft_strlcpy(data->textures.west_texture, ft_strtrim(segment[1], "\n"), ft_strlen(segment[1]) + 1);
			}
			else if (!ft_strcmp(segment[0], "EA"))
			{
				data->textures.east_texture = (char *)malloc(ft_strlen(segment[1] + 1));
				ft_strlcpy(data->textures.east_texture, ft_strtrim(segment[1], "\n"), ft_strlen(segment[1]) + 1);
			}
			else if (!ft_strcmp(segment[0], "F"))
			{
				if (array_len(segment) != 4 || (!ft_strisdigit(segment[1]) || !ft_strisdigit(segment[2]) || !ft_strisdigit(ft_strtrim(segment[3], "\n"))))
				{
					printf("Unrecognized values on ID \'F\'.\n");
					exit(EXIT_SUCCESS);
				}
				data->textures.floor_color[0] = ft_atoi(segment[1]);
				data->textures.floor_color[1] = ft_atoi(segment[2]);
				data->textures.floor_color[2] = ft_atoi(segment[3]);
			}
			else if (!ft_strcmp(segment[0], "C"))
			{
				if (array_len(segment) != 4 || (!ft_strisdigit(segment[1]) || !ft_strisdigit(segment[2]) || !ft_strisdigit(ft_strtrim(segment[3], "\n"))))
				{
					printf("Unrecognized values on ID \'C\'.\n");
					exit(EXIT_SUCCESS);
				}
				data->textures.floor_color[0] = ft_atoi(segment[1]);
				data->textures.floor_color[1] = ft_atoi(segment[2]);
				data->textures.floor_color[2] = ft_atoi(segment[3]);
			}
		}
		if (segment)
			p_free_resources(segment);
		itr++;
		count++;
		if (count == 6)
			break;
		while (data->map.map && data->map.map[itr] && !ft_strcmp(data->map.map[itr], "\n"))
			itr++;
	}
	if (count < 6)
	{
		printf("Missing IDs in map file.\n");
		exit(EXIT_SUCCESS);
	}
	return (itr);
}

// seems to be working, needs to be refactored later

void	load_map(size_t itr, t_data *data)
{
	char 	**file;
	char	**tmp;
	size_t	idx;
	size_t	idx2;

	file = data->map.map;
	data->map.map = NULL;
	idx = 2;
	while (file[itr] && !ft_strcmp(file[itr], "\n"))
		itr++;
	while (file && file[itr])
	{
		if (file[itr] && ft_strcmp(file[itr], "\n"))
		{
			idx2 = 0;
			tmp = data->map.map;
			data->map.map = (char **)malloc(idx * sizeof(char *));
			while (tmp && tmp[idx2])
			{
				data->map.map[idx2] = (char *)malloc(ft_strlen(tmp[idx2]) + 1);
				ft_strlcpy(data->map.map[idx2], tmp[idx2], ft_strlen(tmp[idx2]) + 1);
				idx2++;
			}
			file[itr] = ft_strtrim(file[itr], "\n"); // this line causes memory leaks; 
			data->map.map[idx2] = (char *)malloc(ft_strlen(file[itr]) + 1);
			ft_strlcpy(data->map.map[idx2], file[itr], ft_strlen(file[itr]) + 1);
			data->map.map[++idx2] = NULL;
			p_free_resources(tmp);
			idx++;
			
		}
		if (file[itr] && !ft_strcmp(file[itr], "\n"))
		{
			p_free_resources(data->map.map);
			data->map.map = NULL;
			break;
		}
		if (file[itr])
			itr++;
	}
	p_free_resources(file);
	if (!data->map.map)
	{
		printf("Couldn't read the map.\n");
		exit(EXIT_SUCCESS);
	}
}

void	check_map(t_data *data)
{
	size_t	width;
	size_t	length;

	width = 0;
	length = 0;
	while (data->map.map[length])
	{
		if (ft_strlen(data->map.map[length]) > width)
			width = ft_strlen(data->map.map[length]);
		if (ft_strchr(data->map.map[length], 'N'))
		{
			data->camera.cam_y = length;	
			data->camera.cam_x = (double)(ft_strchr(data->map.map[length], 'N') - data->map.map[length]);
		}
		length++;
	}
	data->map.map_width = width;
	data->map.map_length = length;
	data->map.block_width = WINDOW_WIDTH / data->map.map_width;
	data->map.block_length = WINDOW_HIGHT / data->map.map_length;
	data->camera.cam_y = (data->camera.cam_y * data->map.block_length) + data->map.block_length / 2;
	data->camera.cam_x = (data->camera.cam_x * data->map.block_width) + data->map.block_width / 2;
	data->camera.dir_x = -1.0;
	data->camera.dir_y = 0.0;
	data->camera.plane_x = 0.0;
	data->camera.plane_y = 0.60;
}

void	parser(int fd, t_data *data)
{
	size_t	len;

	
	data->map.map = NULL;
	data->map.map = read_map(fd, data->map.map);
	len = load_textures(data);
	load_map(len, data);
	check_map(data);
}
