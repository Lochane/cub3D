/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 16:38:14 by malancar          #+#    #+#             */
/*   Updated: 2024/02/24 19:07:30 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"


int inter_check(float angle, float *inter, float *step, int is_horizon) // check the intersection
{
	if (is_horizon)
	{
		if (angle > 0 && angle < 180)
		{
			
			*inter += TILE_SIZE;
			*step *= -1;
			return (-1);
		}
		
	}
	else
	{
		if (!(angle > 90 && angle < 270))
		{
			*inter += TILE_SIZE;
			return (-1);
		}
			*step *= -1;
	}
	return (1);
}

int unit_circle(float angle, char c) // check the unit circle
{
	if (c == 'x')
	{
		if (angle > 0 && angle < 180)
			return (1);
	}
	else if (c == 'y')
	{
		if (angle > 90 && angle < 270 / 2)
			return (1);
	}
	return (0);
}

int		hit_wall(t_data *data, float intersection_x, float intersection_y)
{
	int	x = 0;
	int	y = 0;

	if (intersection_x < 0 | intersection_y < 0)
		return (0);
	x = floor(intersection_x);
	y = floor(intersection_y);

	printf("x = %d, y = %d\n", x, y);
	
	if (y >= data->map.height || x >= data->map.width)
		return (0);
	if (data->map.file[y] && data->map.file[y][x])//?? x <= ft_strlen_float(data->map.file[y]) == data->map[y][x] ??
	{
		//printf("map[%d][%d] = %c\n", y, x, data->map.file[y][x]);
		if (data->map.file[y][x] == '1')
			return (1);
	}
	return (0);
}

int		find_horizontal_intersection(t_data *data, float angle)
{
	float	x_step;
	float	y_step;
	float	intersection_x;
	float	intersection_y;

	intersection_y = 0;
	intersection_x = 0;
	
	double	distance;

	x_step = 1 / tan(angle  * (M_PI / 180));
	y_step = 1;
	//printf("xstep = %f, ystep = %f\n", x_step, y_step);
	//printf("tan = %f\n", tan(angle  * (M_PI / 180)));
	intersection_y =  data->player.y;
	inter_check(angle, &intersection_y, &y_step, 1);
	intersection_x = data->player.x + ((intersection_y - data->player.y) / tan(data->player.angle  * (M_PI / 180)));
	// if ((unit_circle(angle, 'y') && x_step > 0) || (!unit_circle(angle, 'y') && x_step < 0)) // check x_step value
 	// 	 x_step *= -1;
	printf("playerx = %d, playery = %d\n", data->player.x, data->player.y);
	printf("horizontal: ");
	printf("xstep = %f, ystep = %f\n", x_step, y_step);
	
	while (!hit_wall(data, intersection_x, intersection_y + y_step))
	{
		
		printf("intersectionx = %f, intersectiony = %f\n", intersection_x, intersection_y);
		intersection_x += x_step;
		intersection_y += y_step;
	}
	printf(" horizontal : inter_x = %f, inter_y = %f\n", intersection_x, intersection_y);
	distance = sqrt(pow(intersection_x - data->player.x, 2) + pow(intersection_y - data->player.y, 2));
	return (distance);
}

int		find_vertical_intersection(t_data *data, float angle)
{
	float	x_step;
	float	y_step;
	float	intersection_x;
	float	intersection_y;
	int	pixel;
	double	distance;

	y_step = 1 / tan(angle  * (M_PI / 180));
	x_step = 1;
		
	intersection_x = data->player.x;
	pixel = inter_check(angle, &intersection_y, &y_step, 1);
	intersection_y = data->player.y + (intersection_x - data->player.x) / tan(angle  * (M_PI / 180));
	
	 if ((unit_circle(angle, 'x') && x_step > 0) || (!unit_circle(angle, 'x') && x_step < 0)) // check x_step value
 		 y_step *= -1;
	printf("vertical: ");
	while (!hit_wall(data, intersection_x - pixel, intersection_y))
	{
		intersection_x += x_step;
		intersection_y += y_step;
	}
	printf("vertical : inter_x = %f, inter_y = %f\n", intersection_x, intersection_y);
	distance = sqrt(pow(intersection_x - data->player.x, 2) + pow(intersection_y - data->player.y, 2));
	return (distance);
}


void	raycasting(t_data *data)
{
	double	angle;
	//double	angle_max;
	int		ray;
	double	horizontal_inter;
	double	vertical_inter;

	ray = 0;
	init_square_size(data);
	angle = data->player.angle - (data->player.fov / 2);

	//data->player.x += 0.25;
	data->player.y += 0.25;
	
	//printf("angle = %f\n", angle);
	horizontal_inter = find_horizontal_intersection(data, angle);
	vertical_inter = find_vertical_intersection(data, angle);
	printf("horizontal_inter = %f\nvertical inter = %f\n", horizontal_inter, vertical_inter);
	
	/*while (ray <= data->win_width)
	{
		horizontal_inter = find_horizontal_intersection(data);
		vertical_inter = find_vertical_intersection(data);
		if (horizontal_inter <= vertical_inter)
			data->ray.distance = vertical_inter;
		else
		{
			data->ray.distance = horizontal_inter;
			
		}
		//printf("distance = %f\n", data->ray.distance);
		//render_wall(data);
		angle = angle + (data->player.fov / data->win_width);
		ray++;
	}*/
}


void	game_loop(t_data *data)
{
	mini_map(data);
	print_all_rays(data);
	raycasting(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img, 0, 0);
}


void	start_game(t_data *data)
{
	
	mlx_hook(data->win_ptr, 33, 1L << 17, &quit_game, data);
	mlx_hook(data->win_ptr, KeyPress, KeyPressMask, &handle_keypress, data);
	
	game_loop(data);
	mlx_loop(data->mlx_ptr);
}
