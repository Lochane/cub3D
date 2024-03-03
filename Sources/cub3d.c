/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 16:38:14 by malancar          #+#    #+#             */
/*   Updated: 2024/03/03 14:50:32 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"


int inter_check(float angle, float *inter, float *step, int is_horizon) // check the intersection
{
	if (is_horizon)
	{
		if (!(angle > 0 && angle < 180))
		{
			
			//*inter += TILE_SIZE;//why
			return (-1);
		}
		*step *= -1;
		
	}
	else
	{
		if (!(angle > 90 && angle < 270))
		{
			*inter += TILE_SIZE;
			return (-1);
		}
		//printf("xstep = %f\n", *step);
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
		if (angle > 90 && angle < 270)
			return (1);
	}
	return (0);
}

int		is_wall(t_data *data, float intersection_x, float intersection_y)
{
	int	x = 0;
	int	y = 0;

	if (intersection_x < 0 || intersection_y < 0)
		return (1);
	//printf("LA interx = %f, intery = %f\n", intersection_x, intersection_y);

	x = floor(intersection_x);
	y = floor(intersection_y);

	//printf("ICI x = %d, y = %d\n", x, y);
	
	if (y >= data->map.height || x >= data->map.width)
		return (1);
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
	float	first_step;
	//int pixel;
	intersection_y = 0;
	intersection_x = 0;
	
	double	distance;

	//printf("playerx = %f, playery = %f\n", data->player.x, data->player.y);
	//printf("x_step = %f\n", x_step);
	//y_step = 0.5;
	//x_step = 0.288;//comment avoir cette valeur ?
	//y_step = data->player.y - data->map.spawn_y;
	//x_step = ;
	//x_step = y_step / tan(-240 * M_PI / 180) + data->player.x;
//	printf("HERE xstep = %f\n", x_step);
	//printf("xstep = %f, ystep = %f\n", x_step, y_step);
	//printf("tan = %f\n", tan(angle  * (M_PI / 180)));
//	printf("step_y = %f\n", y_step);

	x_step = 1 / tan(angle  * (M_PI / 180));
	y_step = 1;

	first_step =  (data->player.y - data->map.spawn_y);
	

	if (unit_circle(angle, 'y') && x_step > 0)
 	{
		
		first_step *= -1;
	}
	
	intersection_y =  data->player.y - first_step;
	inter_check(angle, &intersection_y, &y_step, 1);
	intersection_x =  (data->player.y - data->map.spawn_y) / tan(-angle * M_PI / 180) + data->player.x;
	if ((unit_circle(angle, 'y') && x_step > 0) || (!unit_circle(angle, 'y') && x_step < 0))
 		x_step *= -1;
	// printf("horizontal: ");
	//printf("xstep = %f, ystep = %f\n", x_step, y_step);
	// printf("intersectionx = %f, intersectiony = %f\n\n", intersection_x, intersection_y);
	// printf("PAR LA intersectionx = %f, intersectiony = %f\n", intersection_x, intersection_y);
	while (!is_wall(data, intersection_x, intersection_y))
	{
		
		//printf("intersectionx = %f, intersectiony = %f\n", intersection_x, intersection_y);
		intersection_x += x_step;
		intersection_y += y_step;
	}
	//printf(" horizontal : inter_x = %f, inter_y = %f\n", intersection_x, intersection_y);
	distance = sqrt(pow(intersection_x - data->player.x, 2) + pow(intersection_y - data->player.y, 2));
	return (distance);
}

int		find_vertical_intersection(t_data *data, float angle)
{
	float	x_step;
	float	y_step;
	float	intersection_x;
	float	intersection_y;
	double	distance;

	x_step = 1;
	y_step = 1 * tan(angle  * (M_PI / 180));
	
	intersection_x = data->player.x - (data->player.x - data->map.spawn_x);// - ou +
	inter_check(angle, &intersection_x, &x_step, 0);
	if (angle > 90 && angle < 270)
	{
		//printf("tan entre 90et 270\n");
		intersection_y = tan(angle * M_PI / 180) * (data->player.x - data->map.spawn_x) + data->player.y;
	}
	else
	{
		//printf("-tan pas entre 90 et 270\n");
		intersection_y = tan(-angle * M_PI / 180) * (data->player.x - data->map.spawn_x) + data->player.y;
	}
	if ((unit_circle(angle, 'x') && y_step > 0) || (!unit_circle(angle, 'x') && y_step < 0)) // check x_step value
 		 y_step *= -1;
	// printf("\n\nvertical: \n");
	// printf("playerx = %f, playery = %f\n", data->player.x, data->player.y);
	// printf("xstep = %f, ystep = %f\n", x_step, y_step);
	// printf("inter_x = %f, inter_y = %f\n", intersection_x, intersection_y);
	while (!is_wall(data, intersection_x, intersection_y))
	{
		//printf("vertical : inter_x = %f, inter_y = %f\n", intersection_x, intersection_y);
		intersection_x += x_step;
		intersection_y += y_step;
	}
	//printf("vertical : inter_x = %f, inter_y = %f\n", intersection_x, intersection_y);
	distance = sqrt(pow(intersection_x - data->player.x, 2) + pow(intersection_y - data->player.y, 2));
	return (distance);
}

void	render_wall(t_data *data, int width)
{
	int height;
	int	floor;
	int	ceiling;
	int	wall;
	
	height = 0;
	wall = (data->ray.distance * data->win_height) / data->map.height;//je met 7 en brut mais faut que je trouve dans quelle case je suis de on char**map
	floor = (data->win_height - wall) / 2;
	ceiling = (data->win_height - wall) / 2;
	//printf("ceiling color = %d\nfloor color = %d\n", data->map.ceiling_color, data->map.floor_color);
	//printf("ceiling = %d\nwall = %d\nfloor = %d\n", ceiling, wall, floor);
	//printf("winheight - dstance = %d", (data->win_height - wall));
	while (height < data->win_height)
	{
		if (height <= ceiling)
		{
			//printf("ceiling: height = %d\n", height);
			data->img.addr[height * data->win_width + width] = BLUE;
		}
		else if (height >= ceiling && height <= ceiling + wall)
		{
			//printf("wall: height = %d\n", height);
			data->img.addr[height * data->win_width + width] = RED;
		}
		else
		{
			//printf("floor: height = %d\n", height);
			data->img.addr[height * data->win_width + width] = GREEN;
		}
		height++;
	}
}

void	raycasting(t_data *data)
{
	double	angle;
	//double	angle_max;
	int		ray;
	double	horizontal_inter;
	double	vertical_inter;
	int		width;
	

	//ray = 0;
	width = 0;
	init_square_size(data);
	angle = data->player.angle - (data->player.fov / 2);

	data->player.x += 0.5;
	data->player.y += 0.5;
	horizontal_inter = 0;
	vertical_inter = 0;
	ray = 0;
	//horizontal_inter = find_horizontal_intersection(data, angle);
	//vertical_inter = find_vertical_intersection(data, angle);
	//printf("horizontal_inter = %f\nvertical inter = %f\n", horizontal_inter, vertical_inter);
	
	while (ray < data->win_width)
	{
		horizontal_inter = find_horizontal_intersection(data, angle);
		vertical_inter = find_vertical_intersection(data, angle);
		//printf("horizontale = %f\nverticale = %f\n", horizontal_inter, vertical_inter);
		if (vertical_inter <= horizontal_inter)
			data->ray.distance = vertical_inter;
		else
			data->ray.distance = horizontal_inter;
		//printf("distance = %f\n", data->ray.distance);
		render_wall(data, width);

		//printf("angle = %f\n", angle);
		//printf("ray = %d\n", ray);
		//printf("win_width = %d\n", data->win_width);
		angle = angle + (data->player.fov / (data->win_width - 1));
		ray++;
		width++;//ray = width
		//printf("WIDTH = %d\n", width);
	}
}


void	game_loop(t_data *data)
{
	raycasting(data);
	mini_map(data);
	print_all_rays(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img, 0, 0);
}


void	start_game(t_data *data)
{
	
	mlx_hook(data->win_ptr, 33, 1L << 17, &quit_game, data);
	mlx_hook(data->win_ptr, KeyPress, KeyPressMask, &handle_keypress, data);
	
	game_loop(data);
	mlx_loop(data->mlx_ptr);
}
