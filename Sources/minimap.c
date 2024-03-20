/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 14:14:06 by malancar          #+#    #+#             */
/*   Updated: 2024/03/20 17:58:27 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

void	init_square_size(t_data *data)
{
	int	width;
	int	height;

	data->map.width = count_width(data);
	width = data->map.width;
	height = data->map.height;
	if (width > height)
		data->map.square_size = (data->win_width * ZOOM) / width;
	else
		data->map.square_size = (data->win_height * ZOOM) / height;
}

void	print_square(t_data *data, int start_width, int end_width, int start_height, int end_height, int color)
{
	int	tmp;

	tmp = start_width;
	while (end_height <= data->win_height && start_height <= end_height)
	{
		tmp = start_width;
		while (end_width <= data->win_width && tmp <= end_width)
		{
			data->img.addr[start_height * data->win_width + tmp] = color;
			tmp++;
		}
		start_height++;
	}
}

void	mini_map(t_data *data)
{
	int	i;
	int	j;
	int	x;
	int	y;

	i = 0;
	x = floor(data->player.x);
	y = floor(data->player.y);
	init_square_size(data);
	data->img.height = 0;
	while (data->map.file[i])
	{
		data->img.width = 0;
		j = 0;
		while (data->map.file[i][j])
		{
			if (data->map.file[i][j] == '1')
				print_square(data, data->img.width, data->img.width + data->map.square_size, data->img.height, data->img.height + data->map.square_size, RED);
			else if (data->map.file[i][j] == ' ')
				print_square(data, data->img.width, data->img.width + data->map.square_size, data->img.height, data->img.height + data->map.square_size, BLACK);
			else
				print_square(data, data->img.width, data->img.width + data->map.square_size, data->img.height, data->img.height + data->map.square_size, GREEN);
			if (i == y && j == x)
			{	
				print_square(data, data->img.width, data->img.width + data->map.square_size, data->img.height, data->img.height + data->map.square_size, BLACK);
			}
			j++;
			data->img.width += data->map.square_size;
		}
		data->img.height += data->map.square_size;
		i++;
	}
}

void	display_one_ray(t_data *data, double angle, int wall)
{
	double	a;
	double	b;
	int		x;
	double	y;

	x = data->player.x * data->map.square_size;
	a = -tan(angle * (M_PI / 180));
	b = data->player.y * data->map.square_size - a * x;
	while (x != wall)
	{
		y = a * x + b;
		if (y < 0 || y > data->win_height)
			return ;
		data->img.addr[(int)y * data->win_width + x] = WHITE;
		if (angle >= 90 && angle <= 270)
			x--;
		else
			x++;
	}
}

void	mini_map_rays(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->win_width)
	{
		display_one_ray(data, data->ray.angles[i],
			floor(data->ray.inter_points_x[i] * data->map.square_size));
		i++;
	}
	free(data->ray.angles);
	free(data->ray.inter_points_x);
	free(data->ray.inter_points_y);
}
