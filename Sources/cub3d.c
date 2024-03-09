/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 16:38:14 by malancar          #+#    #+#             */
/*   Updated: 2024/03/09 14:49:50 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"


int inter_check(double angle, double *inter, double *step, int is_horizon) // check the intersection
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

int unit_circle(double angle, char c) // check the unit circle
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

int		is_wall(t_data *data, double intersection_x, double intersection_y, double angle)
{
	int	x = 0;
	int	y = 0;

	if (intersection_x < 0 || intersection_y < 0)
		return (1);
	//printf("LA interx = %f, intery = %f\n", intersection_x, intersection_y);
	if (angle >= 45 && angle <= 135)
	{
		y = floor(intersection_y);
		
	}
	// if (angle >= 90 && angle < 135)
	// {
	// 	x = ceil(intersection_x);
	// }
	else if (angle >= 135 && angle <= 225)
	{
		x = floor(intersection_x);
	}
	//x et y pas forcement les deux floor 
	else if(angle >= 225 && angle <= 315)
	{
		x = ceil(intersection_x);
		//y = floor(intersection_y);
	}
	else if ((angle >= 0 && angle <= 45) || (angle >= 315 && angle <= 360))
	{
		y = ceil(intersection_y);
	}

	//printf("ICI x = %d, y = %d\n", x, y);
	
	if (y >= data->map.height || x >= data->map.width)
		return (1);
	if (data->map.file[y] && data->map.file[y][x])//?? x <= ft_strlen_double(data->map.file[y]) == data->map[y][x] ??
	{
		//printf("map[%d][%d] = %c\n", y, x, data->map.file[y][x]);
		if (data->map.file[y][x] == '1')
			return (1);
	}
	return (0);
}

double		find_horizontal_intersection(t_data *data, double angle)
{
	double	x_step;
	double	y_step;
	double	intersection_x;
	double	intersection_y;
	double	first_step_x;
	double	first_step_y;
	//int pixel;
	intersection_y = 0;
	intersection_x = 0;
	
	double	distance;

	x_step = 1 / tan(angle  * (M_PI / 180));
	y_step = 1;
	first_step_x = x_step;
	first_step_y = y_step;
	if ((angle >= 225 && angle <= 315) || (angle >= 45 && angle <= 135))
	{
		first_step_x =  fmod(data->player.center_x, 1) / tan(angle * M_PI / 180);
		first_step_y = fmod(data->player.center_y, 1);
		printf("first_step_x = %f\nfirst_step_y = %f\n", first_step_x, first_step_y);
		if (angle > 0 && angle < 180)
		{
			first_step_y *= -1;
			first_step_x *= -1;
		}
		intersection_y =  data->player.center_y + first_step_y;
		inter_check(angle, &intersection_y, &y_step, 1);
		intersection_x = data->player.center_x - first_step_x;
		if ((unit_circle(angle, 'y') && x_step > 0) || (!unit_circle(angle, 'y') && x_step < 0))
			x_step *= -1;
	}
	
	printf("horizontal: \n");
	//printf("playerx = %f, playery = %f\n", data->player.x, data->player.y);

	printf("xstep = %f, ystep = %f\n", x_step, y_step);
	printf("intersectionx = %f, intersectiony = %f\n", intersection_x, intersection_y);
	// printf("PAR LA intersectionx = %f, intersectiony = %f\n", intersection_x, intersection_y);
	while (!is_wall(data, intersection_x, intersection_y, angle))
	{
		
		printf("intersectionx = %f, intersectiony = %f\n", intersection_x, intersection_y);
		intersection_x += x_step;
		intersection_y += y_step;
	}
	printf(" horizontal : inter_x = %f, inter_y = %f\n", intersection_x, intersection_y);
	distance = sqrt(pow(intersection_x - data->player.x, 2) + pow(intersection_y - data->player.y, 2));
	return (distance);
}

double		find_vertical_intersection(t_data *data, double angle)
{
	double	x_step;
	double	y_step;
	double	intersection_x;
	double	intersection_y;
	double	first_step_x;
	double	first_step_y;
	double	distance;
	//double		first_step;

	x_step = 1;
	y_step = 1 * tan(-angle  * (M_PI / 180));
	first_step_x = x_step;
	first_step_y = y_step;
	if ((angle >= 135 && angle <= 225) || (angle >= 0 && angle <= 45) || (angle >= 315 && angle <= 360))
	{
		first_step_y =  fmod(data->player.center_y, 1) / tan(angle * M_PI / 180);
		first_step_x = fmod(data->player.center_x, 1);
		printf("first_step_x = %f\nfirst_step_y = %f\n", first_step_x, first_step_y);
		if (angle > 0 && angle < 180)
		{
			first_step_y *= -1;
			first_step_x *= -1;
		}
	}
	
	// first_step = data->player.center_x - data->map.spawn_x;
	// if (angle > 90 && angle < 270)
	// 	first_step *= -1;
	printf("\n\nvertical: \n");
	//printf("first_step = %f\n", first_step);
	intersection_x = data->player.center_x + first_step_x;
	//printf("interx = %f\n", intersection_x);
	//if (angle > 90 && angle < 180)
	//intersection_x = data->player.center_x + (data->player.center_x - data->map.spawn_x);
	inter_check(angle, &intersection_x, &x_step, 0);
	intersection_y = tan(angle * M_PI / 180)  + data->player.y;
	//intersection_y = tan(-angle * M_PI / 180) * (data->player.center_x - data->map.spawn_x) + data->player.y;
	//ca change rien tan(angle) tan(-angle) ?
	
	if ((unit_circle(angle, 'x') && y_step > 0) || (!unit_circle(angle, 'x') && y_step < 0)) // check x_step value
 		 y_step *= -1;
	//printf("playerx = %f, playery = %f\n", data->player.center_x, data->player.y);
	//printf("xstep = %f, ystep = %f\n", x_step, y_step);
	printf("inter_x = %f, inter_y = %f\n", intersection_x, intersection_y);
	while (!is_wall(data, intersection_x, intersection_y, angle))
	{
		printf("vertical : inter_x = %f, inter_y = %f\n", intersection_x, intersection_y);
		intersection_x += x_step;
		intersection_y += y_step;
	}
	printf("vertical : inter_x = %f, inter_y = %f\n", intersection_x, intersection_y);
	distance = sqrt(pow(intersection_x - data->player.center_x, 2) + pow(intersection_y - data->player.y, 2));
	printf("distance = %f\n", distance);
	return (distance);
}

void	render_wall(t_data *data, int width, double angle)
{
	int height;
	int	floor;
	int	ceiling;
	int	wall;
	
	height = 0;
	wall = cos((angle - data->player.angle) * M_PI / 180) * data->ray.distance * 300;
	if (wall < 0)
		wall *= -1;
	printf("wall = %d\n", wall);
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
		data->ray.distance = horizontal_inter;
		if (vertical_inter <= horizontal_inter)
			data->ray.distance = vertical_inter;
		printf("angle = %f\n", angle);
		printf("horizontale = %f\nverticale = %f\n", horizontal_inter, vertical_inter);
		printf("distance = %f\n", data->ray.distance);
		render_wall(data, width, angle);

		//printf("win_width = %d\n", data->win_width);
		angle = angle + (data->player.fov / (data->win_width - 1));
		ray++;
		width++;//ray = width
		printf("ray = %d\n\n", ray);
		//printf("WIDTH = %d\n", width);
	}
}


int	game_loop(t_data *data)
{
	raycasting(data);
	mini_map(data);
	print_all_rays(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img, 0, 0);
	return (0);
}


void	start_game(t_data *data)
{
	
	mlx_hook(data->win_ptr, 33, 1L << 17, &quit_game, data);
	mlx_hook(data->win_ptr, KeyPress, KeyPressMask, &handle_keypress, data);
	mlx_key_hook(data->win_ptr, &keybinding, data);
	mlx_loop_hook(data->mlx_ptr, &game_loop, data);
	
	mlx_loop(data->mlx_ptr);
}
