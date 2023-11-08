/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 04:04:27 by bbouagou          #+#    #+#             */
/*   Updated: 2023/10/24 22:50:13 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
#define PARSER_H

#include "common.h"

# define FILEOPENERR "Can't open the map file\n"
# define ARGSERR "Something's wrong with the given arguments.\n"
# define MAPSIZERR "The size of the map doesn't seem right\n"
# define FILEFRMTERR "There's something wrong with the file format\n"
# define NOTXTERR "Can't open NO texture file\n"
# define SOTXTERR "Can't open SO texture file\n"
# define WETXTERR "Can't open WE texture file\n"
# define EATXTERR "Can't open EA texture file\n"
# define PLYRPOSERR "Multiple player starting positions detected\n"
# define NOPLYPOSERR "No player starting position has been detected\n"
# define MAPSTRTERR "The map seems to be not enclosed by walls\n"

void	parser(int fd, t_data *data, int map_len); // parser's main function, takes as an argument a file descriptor to the map's file.

/*
	UTIL FUNCTIONS
*/

bool	string_is_whitespace(char *string);
bool	char_is_whitespace(char c);
bool	string_has_valid_identifier(char *string);
bool	is_map_line(char *string);
bool	valid_coords(t_data	*data, int x, int y, t_list *head);
void	load_component_to_struct(t_data *data, char *string);
void	p_free_resources(char **ptr);
int		array_len(char **ptr);
int		count_map_lines(t_data *data, int idx);

#endif
