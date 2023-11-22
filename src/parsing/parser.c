/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 08:53:12 by bbouagou          #+#    #+#             */
/*   Updated: 2023/11/22 23:13:38 by bbouagou         ###   ########.fr       */
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
	while (data->map.map[idx] && string_is_whitespace(data->map.map[idx]))
		idx++;
	if (data->map.map[idx])
		exit(printf(FILEFRMTERR));
	p_free_resources(data->map.map);
	data->map.map = tmp;
}

void	check_map_components(t_data *data)
{
	bool	flag;
	size_t	idx;
	size_t	idx2;

	idx = 0;
	flag = false;
	while (data->map.map[idx])
	{
		idx2 = 0;
		while(data->map.map[idx][idx2])
		{
			if (ft_strchr("NSWE", data->map.map[idx][idx2]) && flag == true)
				exit(printf(PLYRPOSERR));
			if (ft_strchr("NSWE", data->map.map[idx][idx2]) && flag == false)
			{
				if (data->map.map[idx][idx2] == 'N')
					data->camera.angle = 3 * M_PI / 2;
				else if (data->map.map[idx][idx2] == 'S')
					data->camera.angle = M_PI / 2;
				else if (data->map.map[idx][idx2] == 'W')
					data->camera.angle = M_PI;
				else if (data->map.map[idx][idx2] == 'E')
					data->camera.angle = 0;
				data->camera.player_x = idx2;
				data->camera.player_y = idx;
				flag = true;
			}
			if (char_is_whitespace(data->map.map[idx][idx2]))
				data->map.map[idx][idx2] = '0';
			idx2++;
		}
		idx++;
	}
	if (flag == false)
		exit(printf(NOPLYPOSERR));
}

void	get_map_dimensions(t_data *data)
{
	size_t	idx;
	size_t	tmp;

	idx = 0;
	tmp = 0;
	data->map.map_height = 0;
	data->map.map_width = 0;
	while (data->map.map[idx])
	{
		tmp = ft_strlen(data->map.map[idx]);
		if (data->map.map_width < (unsigned int)tmp)
			data->map.map_width = (unsigned int)tmp;
		idx++;
	}
	data->map.map_height = (unsigned int)idx;
	if (data->map.map_width > data->map.map_height)
		data->map.ratio = data->map.map_width;
	else
		data->map.ratio = data->map.map_height;
	data->map.block_width = BLOCK;
	data->map.block_height = BLOCK;
	data->camera.player_x = data->camera.player_x * data->map.block_width + data->map.block_width / 2;
	data->camera.player_y = data->camera.player_y * data->map.block_height + data->map.block_height / 2;
	data->camera.dir_x = cos(data->camera.angle) * 2;
	data->camera.dir_y = sin(data->camera.angle) * 2;
	data->north = mlx_load_png(data->textures.north_texture);
	data->south = mlx_load_png(data->textures.south_texture);
	data->east = mlx_load_png(data->textures.east_texture);
	data->west = mlx_load_png(data->textures.west_texture);
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
			len = ft_strlen(data->map.map[idx]) + ((size_t)data->map.map_width - ft_strlen(data->map.map[idx]));
			tmp = (char *)ft_calloc(len + 1, sizeof(char));
			ft_strlcpy(tmp, data->map.map[idx], ft_strlen(data->map.map[idx]) + 1);
			ft_memset((void *)tmp + ft_strlen(data->map.map[idx]), '0', len - ft_strlen(data->map.map[idx]));
			free(data->map.map[idx]);
			data->map.map[idx] = tmp;
		}
		idx++;
	}
}

void	check_map_borders(t_data *data)
{
	t_list	*head;
	t_list	*curr;

	head = ft_lstnew(data->camera.player_x / data->map.block_width, data->camera.player_y / data->map.block_height);
	curr = head;
	while (curr)
	{
		if (curr->x == 0 || curr->y == 0 || curr->x == data->map.map_width - 1 || curr->y == data->map.map_height - 1)
			exit(printf(MAPSTRTERR));
		if (valid_coords(data, curr->x + 1, curr->y, head))
			ft_lstadd_back(&head, ft_lstnew(curr->x + 1, curr->y));
		if (valid_coords(data, curr->x - 1, curr->y, head))
			ft_lstadd_back(&head, ft_lstnew(curr->x - 1, curr->y));
		if (valid_coords(data, curr->x, curr->y + 1, head))
			ft_lstadd_back(&head, ft_lstnew(curr->x, curr->y + 1));
		if (valid_coords(data, curr->x, curr->y - 1, head))
			ft_lstadd_back(&head, ft_lstnew(curr->x, curr->y - 1));
		curr = curr->next;
	}
	ft_lstclear(&head);
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
	check_map_components(data);
	get_map_dimensions(data);
	fill_empty_lines(data);
	check_map_borders(data);
}
