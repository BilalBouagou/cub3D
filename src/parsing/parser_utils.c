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
	while (string[idx] == ' ' || string[idx] == '\t' || string[idx] == '\v' || string[idx] == '\r' || string[idx] == '\f' || string[idx] == '\n')
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
	while (string[idx] && (string[idx] == '0' || string[idx] == '1' || char_is_whitespace(string[idx])))
		idx++;
	if (string[idx] || (string[idx] == '\n' && ft_strlen(string) == 1))
		return (false);
	return (true);
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
		if (!ft_strcmp(tmp[0], "SO") && array_len(tmp) == 2)
			data->textures.south_texture = ft_strdup(ft_strtrim(tmp[1], "\n"));
		else if (!ft_strcmp(tmp[0], "NO") && array_len(tmp) == 2)
			data->textures.north_texture = ft_strdup(ft_strtrim(tmp[1], "\n"));
		else if (!ft_strcmp(tmp[0], "WE") && array_len(tmp) == 2)
			data->textures.west_texture = ft_strdup(ft_strtrim(tmp[1], "\n"));
		else if (!ft_strcmp(tmp[0], "EA") && array_len(tmp) == 2)
			data->textures.east_texture = ft_strdup(ft_strtrim(tmp[1], "\n"));
		else if (!ft_strcmp(tmp[0], "F"))
			load_colors(&(data->textures.floor_color), ft_strtrim(tmp[1], "\n"));
		else if (!ft_strcmp(tmp[0], "C"))
			load_colors(&(data->textures.ceiling_color), ft_strtrim(tmp[1], "\n"));
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