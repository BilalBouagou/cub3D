/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 04:05:23 by bbouagou          #+#    #+#             */
/*   Updated: 2023/08/23 13:45:06 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/common.h"
#include "../inc/parser.h"
#include "../inc/renderer.h"

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

// todo : check file size and return error if file is too big;

int main(int argc, char **argv)
{
	t_data	*data;

	if (argc == 2 && file_is_valid(argv[1]))
	{
		data = (t_data*)malloc(sizeof(t_data));
		parser(open(argv[1], O_RDONLY), data);
        puts("everything went according to plan!");
		// renderer(data);
	}
	else
		printf("Something's wrong with the given arguments.\n");
	return EXIT_SUCCESS;
}
