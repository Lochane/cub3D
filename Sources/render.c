/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 18:52:08 by lsouquie          #+#    #+#             */
/*   Updated: 2024/04/08 17:12:20 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

t_img	get_img(t_data *data)
{
	if (data->ray.is_horizontal == 1)
	{
		if (data->player.y > data->ray.inter_y)
			return (data->texture.so_texture);
		else
			return (data->texture.no_texture);
	}
	else
	{
		if (data->player.x > data->ray.inter_x)
			return (data->texture.ea_texture);
		else
			return (data->texture.we_texture);
	}
}

int	check_calcul(int calcul, t_img img, t_data *data)
{
	if ((data->texture.pixel_x < 0 && data->texture.pixel_x >= data->img.width) \
	|| (data->texture.pixel_y < 0 && data->texture.pixel_y >= data->img.height))
		return (1);
	if (calcul < 0)
		return (1);
	if (calcul > img.width * img.height)
		return (1);
	return (0);
}

int	render_texture(t_data *data, int height, int beg_wall, int end_wall)
{
	const double	block_size = end_wall - beg_wall;
	double			ratio_x;
	double			ratio_y;
	int				calcul;
	const t_img		img = get_img(data);

	if (data->ray.is_horizontal == 0)
		ratio_x = data->ray.inter_y - (int)data->ray.inter_y;
	else
		ratio_x = data->ray.inter_x - (int)data->ray.inter_x;
	data->texture.pixel_x = img.width * (1 - ratio_x);
	ratio_y = (height - beg_wall) / block_size;
	data->texture.pixel_y = (int)(img.height * ratio_y);
	data->ray.dirx = cos(data->ray.angles[data->ray.ray_index] * (M_PI / 180));
	data->ray.diry = sin(data->ray.angles[data->ray.ray_index] * (M_PI / 180));
	if (img.print == 0)
		calcul = ((int)data->texture.pixel_y * img.width) - \
			(int)data->texture.pixel_x;
	else
		calcul = (int)data->texture.pixel_x + \
			(int)data->texture.pixel_y * img.width;
	if (check_calcul(calcul, img, data) != 0)
		return (BLACK);
	return (img.addr[calcul]);
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
			data->img.addr[height * data->win_width + width] = \
				data->map.ceiling_color;
		else if (height >= wall_start && height <= wall_end)
			data->img.addr[height * data->win_width + width] = \
				render_texture(data, height, wall_start, wall_end);
		else
			data->img.addr[height * data->win_width + width] = \
				data->map.floor_color;
		height++;
	}
}
