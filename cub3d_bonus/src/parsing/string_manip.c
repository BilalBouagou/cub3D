/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_manip.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 18:55:35 by bbouagou          #+#    #+#             */
/*   Updated: 2023/11/29 18:56:10 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

bool	string_is_whitespace(char *string)
{
	size_t	idx;

	idx = 0;
	while (string[idx] == ' ' || string[idx] == '\t' || string[idx] == '\v'
		|| string[idx] == '\r' || string[idx] == '\f')
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
