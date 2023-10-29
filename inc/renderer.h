/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-hadr < yel-hadr@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 04:04:47 by bbouagou          #+#    #+#             */
/*   Updated: 2023/10/29 04:47:32 by yel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERER_H
#define RENDERER_H

#include "common.h"


void draw_player(t_data* data);
void ft_error(char	*str);
void draw_player(t_data *data);
void draw_line(t_data *data, int x1, int y1, int x2, int y2, int color);
int	get_rgba(int r, int g, int b, int a);
void	renderer(t_data *data);

#endif