/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 18:52:08 by lsouquie          #+#    #+#             */
/*   Updated: 2024/03/15 19:13:27 by lsouquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"


t_img get_img(t_data *data)
{
	printf("%f\n", data->player.angle);
	if (data->ray.is_horizontal == 0)
	{
		//ouest est
		if (data->player.angle >= 90 &&  data->player.angle <= 270)
			return (data->texture.we_texture);
		else
			return (data->texture.ea_texture);
	}
	else
	{
		if (data->player.angle >= 180 &&  data->player.angle <= 360)
			return (data->texture.so_texture);
		else
			return (data->texture.no_texture);
	}
}

int	render_texture(t_data *data, int height, int beg_wall, int end_wall)
{
	double	block_size;
	double	ratio_x;
	double	ratio_y;
	t_img	img;

	img = get_img(data);
//	printf("-------------New pixel Rendering ----------------\n");
	if (data->ray.is_horizontal == 0)
		ratio_x = data->ray.inter_y - (int)data->ray.inter_y;
	else
		ratio_x = data->ray.inter_x - (int)data->ray.inter_x;

	data->texture.pixel_x = img.width * ratio_x;
	block_size = end_wall - beg_wall;
	ratio_y = (height - beg_wall) / block_size;
//	printf("ratio x = %f, ration_y = %f, img_width = %i\n", ratio_x, ratio_y, img.width);
	data->texture.pixel_y = (int)(img.height * ratio_y);
//		printf("pixel x = %f, pixel y = %f\n", data->texture.pixel_x, data->texture.pixel_y);
	return (img.addr[(int)data->texture.pixel_x + (int)data->texture.pixel_y* img.width]);
}

