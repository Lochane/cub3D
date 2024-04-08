/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 15:13:18 by malancar          #+#    #+#             */
/*   Updated: 2024/04/08 17:06:04 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

int	is_wall(t_data *data, double intersection_x, double intersection_y,
	double angle)
{
	int	x;
	int	y;

	if (intersection_x < 0 || intersection_y < 0)
		return (1);
	else if (intersection_x >= INT_MAX || intersection_y >= INT_MAX)
		return (INT_MAX);
	if (angle >= 90 && angle <= 270)
		x = ceil(intersection_x) - 1;
	else
		x = floor(intersection_x);
	if (angle >= 0 && angle <= 180)
		y = ceil(intersection_y) - 1;
	else
		y = floor(intersection_y);
	if (y < 0 || y >= data->map.height || x < 0 || x >= data->map.width)
		return (1);
	if (y >= 0 && data->map.file[y] && (x < (int)ft_strlen(data->map.file[y])
			&& x >= 0 && data->map.file[y][x]))
	{
		if (data->map.file[y][x] == '1')
			return (1);
	}
	return (0);
}

double	fix_angle(double angle)
{
	while (angle < 0)
		angle += 360;
	while (angle >= 360)
		angle -= 360;
	return (angle);
}

void	set_distance(t_data *data, double horizontal_inter,
		double vertical_inter, double angle)
{
	data->ray.distance = horizontal_inter;
	data->ray.inter_x = data->ray.h_inter_x;
	data->ray.inter_y = data->ray.h_inter_y;
	data->ray.is_horizontal = 1;
	if (vertical_inter <= horizontal_inter)
	{
		data->ray.inter_x = data->ray.v_inter_x;
		data->ray.inter_y = data->ray.v_inter_y;
		data->ray.distance = vertical_inter;
		data->ray.is_horizontal = 0;
	}
	data->ray.distance *= fabs(cos((angle - data->player.angle)
				* M_PI / 180));
}

void	raycasting(t_data *data)
{
	double	angle;
	int		ray;
	double	horizontal_inter;
	double	vertical_inter;

	ray = 0;
	init_square_size(data);
	data->player.angle = fix_angle(data->player.angle);
	angle = data->player.angle - (data->player.fov / 2);
	data->ray.inter_points_x = malloc(sizeof(double) * data->win_width);
	data->ray.angles = malloc(sizeof(double) * data->win_width);
	ft_bzero(data->ray.angles, data->win_width);
	while (ray < data->win_width)
	{
		angle = fix_angle (angle);
		horizontal_inter = find_horizontal_intersection(data, angle);
		vertical_inter = find_vertical_intersection(data, angle);
		set_distance(data, horizontal_inter, vertical_inter, angle);
		render_wall(data, (data->win_width - 1) - ray);
		angle = angle + (data->player.fov / (data->win_width - 1));
		data->ray.angles[ray] = angle;
		data->ray.inter_points_x[ray] = data->ray.inter_x;
		ray++;
	}
}
