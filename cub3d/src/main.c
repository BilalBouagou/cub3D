/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 04:05:23 by bbouagou          #+#    #+#             */
/*   Updated: 2023/12/01 22:23:38 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/common.h"
#include "../inc/parser.h"
#include "../inc/renderer.h"

// todo : check file size and return error if file is too big;

int32_t	file_is_valid(char *map)
{
	int32_t	map_len;
	int32_t	fd;

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

int32_t	get_file_lines(char *file)
{
	int32_t		count;
	int32_t		fd;
	char		*string;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		exit(printf(FILEOPENERR));
	count = 0;
	string = get_next_line(fd);
	while (string)
	{
		count++;
		free(string);
		string = get_next_line(fd);
	}
	close(fd);
	return (count);
}

int32_t	main(int argc, char **argv)
{
	t_data			*data;

	if (argc == 2 && file_is_valid(argv[1]))
	{
		data = (t_data *)malloc(sizeof(t_data));
		ft_memset(data, 0, sizeof(t_data));
		parser(open(argv[1], O_RDONLY), data, get_file_lines(argv[1]));
		renderer(data);
	}
	else
		printf(ARGSERR);
	return (EXIT_SUCCESS);
}
