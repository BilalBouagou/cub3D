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
	size_t	idx;

	idx = 0;
	while (string[idx] == ' ' || string[idx] == '\t' || string[idx] == '\v' || string[idx] == '\r' || string[idx] == '\f')
		idx++;
	if ((!ft_strncmp(&string[idx], "SO", 2) || !ft_strncmp(&string[idx], "NO", 2) || !ft_strncmp(&string[idx], "WE", 2) || !ft_strncmp(&string[idx], "EA", 2)) && char_is_whitespace(string[idx + 2]))
		return (true);
	return (false);
}

bool	is_map_line(char *string)
{
	size_t	idx;

	idx = 0;
	while (string[idx] && (string[idx] == '0' || string[idx] == '1' || char_is_whitespace(string[idx])))
		idx++;
	if (string[idx] && string[idx] != '\n')
		return (false);
	return (true);
}

void	load_component_to_struct(t_data *data, char *string)
{
	size_t	idx;

	idx = 0;
	while (string[idx] && char_is_whitespace(string[idx]))
		idx++;
	if (!ft_strncmp(&string[idx], "SO", 2) && char_is_whitespace(string[idx + 2]))
		// to be continued ...
}

int		array_len(char **ptr)
{
	int	i;

	i = 0;
	while (ptr && ptr[i])
		i++;
	return (i);
}