/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-hadr < yel-hadr@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 04:11:27 by bbouagou          #+#    #+#             */
/*   Updated: 2023/11/02 00:51:45 by yel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
#define COMMON_H

#include "../libft/libft.h"
#include "../MLX42/include/MLX42/MLX42.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>

#define WINDOW_HEIGHT 580
#define WINDOW_WIDTH 1080

#define BLOCK 32
#define PI 3.1415926535897
#define DEGRE 0.0174533
#define FOV_ANGLE 60
#define DISTANCE_PROJ_PLANE ((WINDOW_WIDTH / 2) / tan(FOV_ANGLE / 2 * DEGRE))
#define RAYS_NUMBER (WINDOW_WIDTH / FOV_ANGLE)
#define BPP sizeof(int32_t)

struct s_map
{
	char			**map;
	unsigned int	map_width;
	unsigned int	map_height;
	unsigned int	block_width;
	unsigned int	block_height;
	unsigned int	ratio;
};

struct s_camera
{
	double			angle;
	double			dir_x;
	double			dir_y;
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

typedef enum	e_direction
{
	NO_DIRECTION,
	NORTH,
	SOUTH,
	EAST,
	WEST
}	t_direc;

typedef enum e_wall
{
	HORIZONTAL,
	VERTICAL,
	NO_WALL
}	t_wall;

typedef struct	s_ray
{
	double	angle;
	double	dir_x;
	double	dir_y;
	double	distance;
	t_direc	north_south;
	t_direc	east_west;
	t_wall	wall;
} t_ray;

typedef struct s_data
{
	mlx_t*				mlx;
	mlx_image_t*		img;
	struct s_map		map;
	struct s_camera		camera;
	struct s_textures	textures;
	struct s_ray		ray[WINDOW_WIDTH];
}	t_data;


#endif
