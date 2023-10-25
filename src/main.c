/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 04:05:23 by bbouagou          #+#    #+#             */
/*   Updated: 2023/10/25 05:13:20 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/common.h"
#include "../inc/parser.h"
#include "../inc/renderer.h"

// todo : check file size and return error if file is too big;

int		file_is_valid(char *map)
{
	size_t	map_len;
	int		fd;

	fd = open(map, O_RDONLY);
	map_len = ft_strlen(map);
	if (map_len > 4 && fd != -1)
	{
		close(fd);
		if (!ft_strncmp(&map[map_len - 4], ".cub", 4))
			return (1);
	}
	return (0);
}

int	get_file_lines(char *file)
{
	int	count;
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == - 1)
		exit(printf(FILEOPENERR));
	count = 0;
	while (get_next_line(fd))
		count++;
	close(fd);
	return (count);
}

int main(int argc, char **argv)
{
	t_data	*data;

	if (argc == 2 && file_is_valid(argv[1]))
	{
		data = (t_data*)malloc(sizeof(t_data));
		parser(open(argv[1], O_RDONLY), data, get_file_lines(argv[1]));
		data->map.block_width = WINDOW_WIDTH / data->map.map_width;
		data->map.block_height = WINDOW_HEIGHT / data->map.map_height;
		renderer(data);
	}
	else
		printf(ARGSERR);
	return EXIT_SUCCESS;
}
