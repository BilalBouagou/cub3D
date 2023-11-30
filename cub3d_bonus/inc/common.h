/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-hadr < yel-hadr@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 04:11:27 by bbouagou          #+#    #+#             */
/*   Updated: 2023/11/30 22:05:25 by yel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H

# include "../libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <limits.h>
# include <math.h>
# include <stdbool.h>

# define WINDOW_HEIGHT 900
# define WINDOW_WIDTH 1600

# define MINIMAP_HEIGHT 136
# define MINIMAP_WIDTH 362

# define BLOCK 64
# define PI 3.1415926535897
# define DEGRE 0.0174533
# define FOV_ANGLE 60
# define DISTANCE_PROJ_PLANE ((WINDOW_WIDTH / 2) / tan(FOV_ANGLE / 2 * DEGRE))
# define RAYS_NUMBER WINDOW_WIDTH
# define BPP sizeof(int32_t)
# define SPEED 4

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
	float			angle;
	float			dir_x;
	float			dir_y;
	float			player_x;
	float			player_y;
};

struct s_textures
{
	char			*north_texture;
	char			*south_texture;
	char			*east_texture;
	char			*west_texture;
	unsigned int	floor_color;
	unsigned int	ceiling_color;
};

typedef enum e_direction
{
	NO_DIRECTION,
	NORTH,
	SOUTH,
	EAST,
	DOOR,
	WEST
}	t_direc;

typedef enum e_wall
{
	HORIZONTAL,
	VERTICAL,
	NO_WALL
}	t_wall;

typedef struct s_ray
{
	int		offset_x;
	float	angle;
	float	dir_x;
	float	dir_y;
	float	distance;
	float	wall_strip_height;
	float	yintercept;
	float	xintercept;
	float	xstep;
	float	ystep;
	float next_x;
	float next_y;
	int32_t	color;
	int32_t	wall_bottom;
	int32_t	wall_top;
	t_direc	north_south;
	t_direc	east_west;
	t_direc	is_door;
	t_wall	wall;
}	t_ray;

typedef struct s_data
{
	mlx_t				*mlx;
	mlx_image_t			*img;
	mlx_image_t			*status_bar_img;
	mlx_image_t			*gun_img;
	mlx_image_t			*minimap_img;
	struct s_map		map;
	struct s_camera		camera;
	struct s_textures	textures;
	mlx_texture_t		*north;
	mlx_texture_t		*south;
	mlx_texture_t		*east;
	mlx_texture_t		*west;
	mlx_texture_t		*doors;
	mlx_texture_t		*status_bar;
	xpm_t				*gun_1;
	xpm_t				*gun_2;
	xpm_t				*gun_3;
	xpm_t				*gun_4;
	int					anim_count;
}	t_data;

int	get_rgba(int r, int g, int b, int a);

#endif
