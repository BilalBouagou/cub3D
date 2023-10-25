/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-hadr < yel-hadr@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 13:26:05 by bbouagou          #+#    #+#             */
/*   Updated: 2023/10/25 03:44:23 by yel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/renderer.h"

void	ft_rending(t_data *data)
{
	data->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HIGHT, "Cub3D", false);
	if (!data->mlx)
	{
		ft_putstr_fd((char *)mlx_strerror(mlx_errno), 2);
		exit (EXIT_FAILURE);
	}
	data->img = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_HIGHT);
	if (!data->img)
	{
		mlx_close_window(data->mlx);
		ft_putstr_fd((char *)mlx_strerror(mlx_errno), 2);
		exit (EXIT_FAILURE);
	}
}