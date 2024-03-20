/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 18:52:08 by lsouquie          #+#    #+#             */
/*   Updated: 2024/03/20 19:55:07 by lsouquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"


t_img	get_img(t_data *data)
{
	if (data->ray.is_horizontal)
	{
		if (data->ray.diry > 0)
			return (data->texture.no_texture);
		else
			return (data->texture.so_texture);
	}
	else
	{
		if (data->ray.dirx > 0)
			return (data->texture.ea_texture);
		else
			return (data->texture.we_texture);
	}
}

int	render_texture(t_data *data, int height, int beg_wall, int end_wall)
{
	double	block_size;
	double	ratio_x;
	double	ratio_y;
	t_img	img;

	img = get_img(data);
	if (data->ray.is_horizontal == 0)
		ratio_x = data->ray.inter_y - (int)data->ray.inter_y;
	else
		ratio_x = data->ray.inter_x - (int)data->ray.inter_x;
	data->texture.pixel_x = img.width * ratio_x;
	block_size = end_wall - beg_wall;
	ratio_y = (height - beg_wall) / block_size;
	data->texture.pixel_y = (int)(img.height * ratio_y);
	data->ray.dirx = cos(data->ray.angles[data->ray.ray_index] * (M_PI / 180));
	data->ray.diry = sin(data->ray.angles[data->ray.ray_index] * (M_PI / 180));
	if ((data->texture.pixel_x < 0 && data->texture.pixel_x >= data->img.width) \
	|| (data->texture.pixel_y < 0 && data->texture.pixel_y >= data->img.height))
		return (BLACK);
	if (img.allow == 1)
		return (img.addr[((int)data->texture.pixel_y * img.width ) - (int)data->texture.pixel_x ]);
	return (img.addr[(int)data->texture.pixel_x + \
		(int)data->texture.pixel_y * img.width]);
}
