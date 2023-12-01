/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 11:25:44 by bbouagou          #+#    #+#             */
/*   Updated: 2023/12/01 21:41:55 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

bool	string_has_valid_identifier(char *string)
{
	char	**tmp;

	tmp = ft_split_whitespace(string);
	if (tmp)
	{
		if (!ft_strcmp(tmp[0], "SO") || !ft_strcmp(tmp[0], "NO")
			|| !ft_strcmp(tmp[0], "WE") || !ft_strcmp(tmp[0], "EA")
			|| !ft_strcmp(tmp[0], "F") || !ft_strcmp(tmp[0], "C"))
		{
			p_free_resources(tmp);
			return (true);
		}
	}
	p_free_resources(tmp);
	return (false); 
}

bool	is_map_line(char *string)
{
	size_t	idx;

	idx = 0;
	while (string[idx] && (string[idx] == '0' || string[idx] == '1'
			|| string[idx] == 'D' || ft_strchr("NSWE", string[idx])
			|| char_is_whitespace(string[idx])))
		idx++;
	if (!(*string) || string[idx])
		return (false);
	return (true);
}

int	count_map_lines(t_data *data, int idx)
{
	int	count;

	count = 0;
	while (data->map.map[idx] && is_map_line(data->map.map[idx]))
	{
		idx++;
		count++;
	}
	return (count);
}

void	load_colors(unsigned int **color, char *string)
{
	char	**tmp;
	int		idx;

	tmp = ft_split(string, ',');
	if (*color != NULL)
		exit(printf(FILEFRMTERR));
	*color = (unsigned int *)malloc(sizeof(unsigned int));
	if (tmp && array_len(tmp) == 3)
	{
		idx = -1;
		while (++idx < 3)
			if (!ft_strisdigit(tmp[idx]))
				exit(printf(FILEFRMTERR));
		if (ft_atoi(tmp[0]) > 255
			|| ft_atoi(tmp[1]) > 255 || ft_atoi(tmp[2]) > 255)
			exit(printf(FILEFRMTERR));
		**color = get_rgba(ft_atoi(tmp[0]), ft_atoi(tmp[1]),
				ft_atoi(tmp[2]), 255);
		p_free_resources(tmp);
		return ;
	}
	exit(printf(FILEFRMTERR));
}

void	load_component_to_struct(t_data *data, char *string)
{
	char	**tmp;

	tmp = ft_split_whitespace(string);
	if (tmp)
	{
		if (!data->textures.south_texture
			&& ft_strcmp(tmp[0], "SO") == 0 && array_len(tmp) == 2)
			data->textures.south_texture = ft_strdup(tmp[1]);
		else if (!data->textures.north_texture
			&& ft_strcmp(tmp[0], "NO") == 0 && array_len(tmp) == 2)
			data->textures.north_texture = ft_strdup(tmp[1]);
		else if (!data->textures.west_texture
			&& ft_strcmp(tmp[0], "WE") == 0 && array_len(tmp) == 2)
			data->textures.west_texture = ft_strdup(tmp[1]);
		else if (!data->textures.east_texture
			&& ft_strcmp(tmp[0], "EA") == 0 && array_len(tmp) == 2)
			data->textures.east_texture = ft_strdup(tmp[1]);
		else if (ft_strcmp(tmp[0], "F") == 0 && array_len(tmp) == 2)
			load_colors(&(data->textures.floor_color), tmp[1]);
		else if (ft_strcmp(tmp[0], "C") == 0 && array_len(tmp) == 2)
			load_colors(&(data->textures.ceiling_color), tmp[1]);
		else
			exit(printf(FILEFRMTERR));
		p_free_resources(tmp);
	}
}
