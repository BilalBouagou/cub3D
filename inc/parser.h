/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 04:04:27 by bbouagou          #+#    #+#             */
/*   Updated: 2023/10/20 08:27:44 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
#define PARSER_H

#include "common.h"

# define FILEOPENERR "Can't open the map file\n"
# define ARGSERR "Something's wrong with the given arguments.\n"
# define MAPSIZERR "The size of the map doesn't seem right\n"
# define FILEFRMTERR "There's something wrong with the file format\n"

void	parser(int fd, t_data *data, int map_len); // parser's main function, takes as an argument a file descriptor to the map's file.

/*
	UTIL FUNCTIONS
*/

bool	string_is_whitespace(char *string);
bool	string_has_valid_identifier(char *string);
bool	is_map_line(char *string);
void	load_component_to_struct(t_data *data, char *string);
void	p_free_resources(char **ptr);
int		array_len(char **ptr);

#endif
