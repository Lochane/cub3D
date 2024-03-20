/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 18:52:08 by lsouquie          #+#    #+#             */
/*   Updated: 2024/03/20 17:59:00 by malancar         ###   ########.fr       */
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
	return (img.addr[(int)data->texture.pixel_x + \
		(int)data->texture.pixel_y * img.width]);
}

void	render_wall(t_data *data, int width)
{
	int	height;
	int	wall_start;
	int	wall_end;
	int	wall;

	height = 0;
	wall = (data->win_height * 2) / (data->ray.distance + 1);
	wall_start = (data->win_height - wall) / 2;
	wall_end = wall_start + wall;
	while (height < data->win_height)
	{
		if (height <= wall_start)
			data->img.addr[height * data->win_width + width] = data->map.ceiling_color;
		else if (height >= wall_start && height <= wall_end)
		{
			data->img.addr[height * data->win_width + width] = RED;
			//data->img.addr[height * data->win_width + width] = render_texture(data, height, wall_start, wall_end);
		}
		else
			data->img.addr[height * data->win_width + width] = data->map.floor_color;
		height++;
	}
}
