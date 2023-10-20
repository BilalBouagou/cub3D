/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 04:11:27 by bbouagou          #+#    #+#             */
/*   Updated: 2023/10/20 07:49:07 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
#define COMMON_H

#include "../libft/libft.h"
// #include "../MLX42/include/MLX42/MLX42.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>

#define WINDOW_HIGHT 1080
#define WINDOW_WIDTH 1920

#define BLOCK_HEIGHT 60
#define	BLOCK_WIDTH 60

#define BPP sizeof(int32_t)

struct s_map
{
	char			**map;
	unsigned int	map_width;
	unsigned int	map_length;
};

struct s_camera
{
	unsigned int	player_elevation;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
    double          player_x;
    double          player_y;
};

struct s_textures
{
	char			*north_texture;
	char			*south_texture;
	char			*east_texture;
	char			*west_texture;
	unsigned int	floor_color[3];
	unsigned int	ceiling_color[3];
};

struct	s_ray
{
	double	angle;
	double	dir_x;
	double	dir_y;
	double	camera_x;
	double	distance;	
};

typedef struct s_data
{
	//mlx_t*			mlx;
	// mlx_image_t*	img;
	struct s_map		map;
	struct s_camera		camera;
	struct s_textures	textures;
	struct s_ray		ray[WINDOW_WIDTH];
}	t_data;


#endif
