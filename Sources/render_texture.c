/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 18:52:08 by lsouquie          #+#    #+#             */
/*   Updated: 2024/03/13 16:05:41 by lsouquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"




int	render_texture(t_data *data, int height, int beg_wall, int end_wall, t_img img)
{
	double	block_size;
	double	ratio_x;
	double	ratio_y;
	int		pixel_x;
	int		pixel_y;

	if (data->ray.is_horizontal == 0)
		ratio_x = data->ray.inter_y - (int)data->ray.inter_y;
	else
		ratio_x = data->ray.inter_x - (int)data->ray.inter_x;
	pixel_x = data->img.width * ratio_x;
	block_size = end_wall - beg_wall;
	ratio_y = (height - beg_wall) / block_size;
	pixel_y = (int)(data->img.height * ratio_y);
	return (img.addr[pixel_x * pixel_y]);
}

