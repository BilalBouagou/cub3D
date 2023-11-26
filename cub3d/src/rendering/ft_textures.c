/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_textures.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-hadr < yel-hadr@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 17:41:13 by yel-hadr          #+#    #+#             */
/*   Updated: 2023/11/25 15:44:40 by yel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/renderer.h"

int ft_get_texture_color(t_ray ray, mlx_texture_t *texture)
{
	int offset_y;
	int index;
	offset_y = (ray.wall_top - (WINDOW_HEIGHT / 2) + \
			(ray.wall_strip_height / 2)) * ((float)texture->height / ray.wall_strip_height);
	index = (offset_y * texture->width + ray.offset_x) * 4;
	return (get_rgba(texture->pixels[index], texture->pixels[index + 1], texture->pixels[index + 2], texture->pixels[index + 3]));
}
