/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 04:04:27 by bbouagou          #+#    #+#             */
/*   Updated: 2023/12/01 21:48:52 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "common.h"

# define FILEOPENERR "Error\nCan't open the map file\n"
# define ARGSERR "Error\nSomething's wrong with the given arguments.\n"
# define MAPSIZERR "Error\nThe size of the map doesn't seem right\n"
# define FILEFRMTERR "Error\nThere's something wrong with the file format\n"
# define NOTXTERR "Error\nCan't open NO texture file\n"
# define SOTXTERR "Error\nCan't open SO texture file\n"
# define WETXTERR "Error\nCan't open WE texture file\n"
# define EATXTERR "Error\nCan't open EA texture file\n"
# define PLYRPOSERR "Error\nMultiple player starting positions detected\n"
# define NOPLYPOSERR "Error\nNo player starting position has been detected\n"
# define MAPSTRTERR "Error\nThe map seems to be not enclosed by walls\n"
# define GUNERR "Error\nCan't open gun texture file\n"

void	parser(int fd, t_data *data, int map_len);

/*
	UTIL FUNCTIONS
*/

int		count_map_lines(t_data *data, int idx);
int		array_len(char **ptr);
bool	string_is_whitespace(char *string);
bool	char_is_whitespace(char c);
bool	string_has_valid_identifier(char *string);
bool	is_map_line(char *string);
bool	valid_coords(t_data	*data, int x, int y, t_list *head);
void	load_component_to_struct(t_data *data, char *string);
void	p_free_resources(char **ptr);
void	read_map(int fd, t_data *data);
void	load_map(t_data *data);
void	get_map_dimensions(t_data *data);
void	fill_empty_lines(t_data *data);
void	check_map_components(t_data *data);
void	check_map_borders(t_data *data);

#endif
