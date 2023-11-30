/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-hadr < yel-hadr@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 04:04:47 by bbouagou          #+#    #+#             */
/*   Updated: 2023/11/30 21:31:45 by yel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERER_H
# define RENDERER_H

# include "common.h"

void	draw_player(t_data *data);
void	ft_error(char	*str);
void	draw_player(t_data *data);
void	renderer(t_data *data);
void	draw_walls(t_data *data, t_ray ray, int x);
void	ft_3d_projection(t_data *data, t_ray ray, int x);
bool	ft_haswallat(t_data *data, double x, double y, t_ray *ray);
bool	ft_hasdoor(t_data *data, double x, double y);
float	distance(float x1, float y1, float x2, float y2);
double	normalize_angle(double angle);
int		get_texture(t_ray ray, mlx_texture_t *texture);
t_ray	horizontal_check(t_data *data, double ray_angle);
t_ray	vertical_check(t_data *data, double ray_angle);
t_ray	cast_ray(t_data *data, double ray_angle);
t_direc	get_direction( double ray_angle, bool flag);

#endif