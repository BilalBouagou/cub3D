/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 04:04:27 by bbouagou          #+#    #+#             */
/*   Updated: 2023/08/21 03:05:38 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
#define PARSER_H

#include "common.h"

void	parser(int fd, t_data *data); // parser's main function, takes as an argument a file descriptor to the map's file.

/*
	UTIL FUNCTIONS
*/

void	p_free_resources(char **ptr);
int		array_len(char **ptr);

#endif