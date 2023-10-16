/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 04:04:27 by bbouagou          #+#    #+#             */
/*   Updated: 2023/10/16 01:20:39 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
#define PARSER_H

#include "common.h"

# define FILEOPENERR "Can't open the map file\n"
# define ARGSERR "Something's wrong with the given arguments.\n"
# define MAPSIZERR "The size of the map doesn't seem right\n"

void	parser(int fd, t_data *data, int map_len); // parser's main function, takes as an argument a file descriptor to the map's file.

/*
	UTIL FUNCTIONS
*/

void	p_free_resources(char **ptr);
int		array_len(char **ptr);

#endif
