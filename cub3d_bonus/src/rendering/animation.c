/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 23:43:18 by bbouagou          #+#    #+#             */
/*   Updated: 2023/12/01 00:29:56 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/renderer.h"

void	put_image(t_data *data, mlx_texture_t *texture, bool flag)
{
	mlx_delete_image(data->mlx, data->gun_img);
	data->gun_img = mlx_texture_to_image(data->mlx, texture);
	if (!data->gun_img)
		ft_error((char *)mlx_strerror(mlx_errno));
	mlx_image_to_window(data->mlx, data->gun_img,
		WINDOW_WIDTH / 3 + WINDOW_WIDTH / 18, 408);
	if (flag == true)
		data->anim_count++;
}

void	gun_anim(t_data *data)
{
	if (data->anim_count == 0)
		put_image(data, &data->gun_1->texture, false);
	else if (data->anim_count < 10)
		put_image(data, &data->gun_2->texture, true);
	else if (data->anim_count < 20)
		put_image(data, &data->gun_3->texture, true);
	else if (data->anim_count < 30)
		put_image(data, &data->gun_4->texture, true);
	else if (data->anim_count == 30)
	{
		put_image(data, &data->gun_1->texture, true);
		data->anim_count = 0;
	}
	else
		data->anim_count++;
}
