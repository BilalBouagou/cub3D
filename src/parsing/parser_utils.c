/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 11:25:44 by bbouagou          #+#    #+#             */
/*   Updated: 2023/10/20 08:32:02 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

void	p_free_resources(char **ptr)
{
	size_t idx;

	if (ptr)
	{
		idx = 0;
		while (ptr[idx])
		{
			free (ptr[idx]);
			idx++;
		}
		free (ptr);
	}
}

bool	string_is_whitespace(char *string)
{
	size_t	idx;

	idx = 0;
	while (string[idx] == ' ' || string[idx] == '\t' || string[idx] == '\v' || string[idx] == '\r' || string[idx] == '\f')
		idx++;
	if (string[idx])
		return (false);
	return (true);
}

bool	char_is_whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\v' || c == '\r' || c == '\f')
		return (true);
	return (false);
}

bool	string_has_valid_identifier(char *string)
{
	char **tmp;

	tmp = ft_split_whitespace(string);
	if (tmp)
	{
		if (!ft_strcmp(tmp[0], "SO") || !ft_strcmp(tmp[0], "NO") || !ft_strcmp(tmp[0], "WE") || !ft_strcmp(tmp[0], "EA") || !ft_strcmp(tmp[0], "F") || !ft_strcmp(tmp[0], "C"))
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
	while (string[idx] && (string[idx] == '0' || string[idx] == '1' || ft_strchr("NSWE", string[idx]) || char_is_whitespace(string[idx])))
		idx++;
	if (!(*string) || string[idx])
		return (false);
	return (true);
}

int		count_map_lines(t_data *data, int idx)
{
	int count;

	count = 0;
	while (data->map.map[idx] && is_map_line(data->map.map[idx]))
	{
		idx++;
		count++;
	}
	return (count);
}

void	load_colors(unsigned int (*arr)[3], char *string)
{
	char 	**tmp;
	int		idx;

	tmp = ft_split(string, ',');
	if (tmp && array_len(tmp) == 3)
	{
		idx = -1;
		while (++idx < 3)
			if (!ft_strisdigit(tmp[idx]))
				exit(printf(FILEFRMTERR));
		(*arr)[0] = ft_atoi(tmp[0]);
		(*arr)[1] = ft_atoi(tmp[1]);
		(*arr)[2] = ft_atoi(tmp[2]);
		p_free_resources(tmp);
		return;
	}
	exit(printf(FILEFRMTERR));
}

void	load_component_to_struct(t_data *data, char *string)
{
	char **tmp;

	tmp = ft_split_whitespace(string);
	if (tmp)
	{
		if (ft_strcmp(tmp[0], "SO") == 0 && array_len(tmp) == 2)
			data->textures.south_texture = ft_strdup(tmp[1]);
		else if (ft_strcmp(tmp[0], "NO") == 0 && array_len(tmp) == 2)
			data->textures.north_texture = ft_strdup(tmp[1]);
		else if (ft_strcmp(tmp[0], "WE") == 0 && array_len(tmp) == 2)
			data->textures.west_texture = ft_strdup(tmp[1]);
		else if (ft_strcmp(tmp[0], "EA") == 0 && array_len(tmp) == 2)
			data->textures.east_texture = ft_strdup(tmp[1]);
		else if (ft_strcmp(tmp[0], "F") == 0)
			load_colors(&(data->textures.floor_color), tmp[1]);
		else if (ft_strcmp(tmp[0], "C") == 0)
			load_colors(&(data->textures.ceiling_color), tmp[1]);
		else
			exit(printf(FILEFRMTERR));
		p_free_resources(tmp);
	}
}

int		array_len(char **ptr)
{
	int	i;

	i = 0;
	while (ptr && ptr[i])
		i++;
	return (i);
}