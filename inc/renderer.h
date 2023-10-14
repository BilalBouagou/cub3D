/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 04:04:47 by bbouagou          #+#    #+#             */
/*   Updated: 2023/08/27 18:27:17 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERER_H
#define RENDERER_H

#include "common.h"

/*
	RENDERER'S MAIN FUNCTION
*/

void	renderer(t_data *data);

/*
	UTILS FUNCTIONS
*/

double	deg_to_rad(double value);

#endif