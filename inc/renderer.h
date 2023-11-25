/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-hadr < yel-hadr@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 04:04:47 by bbouagou          #+#    #+#             */
/*   Updated: 2023/11/23 19:48:28 by yel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERER_H
#define RENDERER_H

#include "common.h"


void	draw_player(t_data* data);
void	ft_error(char	*str);
void	draw_player(t_data *data);
void	draw_line(t_data *data, int x1, int y1, int x2, int y2, int color);
void	renderer(t_data *data);
int		get_rgba(int r, int g, int b, int a);
float	distance(float x1, float y1, float x2, float y2);
int		ft_get_texture_color(t_ray ray, mlx_texture_t *texture);
bool	ft_haswallat(t_data *data, double x, double y);
double	normalize_angle(double angle);
void	ft_3d_projection(t_data *data, t_ray ray, int x);
void	draw_walls(t_data *data, t_ray ray, int x);
t_ray	horizontal_check(t_data *data, double ray_angle);
t_ray	vertical_check(t_data *data, double ray_angle);
t_ray	cast_ray(t_data *data, double ray_angle);
t_direc get_direction( double ray_angle, bool flag);


#endif