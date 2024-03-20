/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_intersections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 15:31:29 by malancar          #+#    #+#             */
/*   Updated: 2024/03/20 15:55:34 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

void	horizontal_first_step(t_data *data, double *inter_x, double *inter_y,
	double angle)
{
	double	first_step_x;
	double	first_step_y;
	double	x_step;

	x_step = 1 / tan((angle) * (M_PI / 180));
	if (angle >= 0 && angle <= 180)
	{
		first_step_y = data->player.y - floor(data->player.y);
		first_step_y *= -1;
	}
	else
		first_step_y = data->player.y - ceil(data->player.y);
	first_step_x = first_step_y * x_step;
	if (angle >= 0 && angle <= 180)
		first_step_x *= -1;
	else
		first_step_y *= -1;
	*inter_y = data->player.y + first_step_y;
	*inter_x = data->player.x + first_step_x;
}

double	find_horizontal_intersection(t_data *data, double angle)
{
	double	x_step;
	double	y_step;
	double	intersection_x;
	double	intersection_y;
	double	distance;

	x_step = 1 / tan((angle) * (M_PI / 180));
	y_step = 1;
	horizontal_first_step(data, &intersection_x, &intersection_y, angle);
	if (angle >= 180 && angle < 360)
		x_step *= -1;
	else
		y_step *= -1;
	while (!is_wall(data, intersection_x, intersection_y, angle))
	{
		intersection_x += x_step;
		intersection_y += y_step;
	}
	distance = sqrt(pow(intersection_x - data->player.x, 2)
			+ pow(intersection_y - data->player.y, 2));
	data->ray.h_inter_x = intersection_x;
	data->ray.h_inter_y = intersection_y;
	return (distance);
}

void	vertical_first_step(t_data *data, double *inter_x, double *inter_y,
	double angle)
{
	double	first_step_x;
	double	first_step_y;
	double	y_step;

	y_step = tan((angle) * (M_PI / 180));
	if (angle >= 90 && angle <= 270)
	{
		first_step_x = data->player.x - floor(data->player.x);
		first_step_x *= -1;
	}
	else
		first_step_x = data->player.x - ceil(data->player.x);
	first_step_y = first_step_x * y_step;
	if (angle >= 90 && angle <= 270)
		first_step_y *= -1;
	else
		first_step_x *= -1;
	*inter_x = data->player.x + first_step_x;
	*inter_y = data->player.y + first_step_y;
}

double	find_vertical_intersection(t_data *data, double angle)
{
	double	x_step;
	double	y_step;
	double	intersection_x;
	double	intersection_y;
	double	distance;

	x_step = 1;
	y_step = tan((angle) * (M_PI / 180));
	vertical_first_step(data, &intersection_x, &intersection_y, angle);
	if ((y_step < 0 && !(angle >= 0 && angle <= 180))
		|| (y_step > 0 && angle >= 0 && angle <= 180))
		y_step *= -1;
	if (angle >= 90 && angle <= 270)
		x_step *= -1;
	while (!is_wall(data, intersection_x, intersection_y, angle))
	{
		intersection_x += x_step;
		intersection_y += y_step;
	}
	distance = sqrt(pow(intersection_x - data->player.x, 2)
			+ pow(intersection_y - data->player.y, 2));
	data->ray.v_inter_x = intersection_x;
	data->ray.v_inter_y = intersection_y;
	return (distance);
}
