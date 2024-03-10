/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 16:38:14 by malancar          #+#    #+#             */
/*   Updated: 2024/03/10 18:57:51 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"


int inter_check(double angle, double *inter, double *step, int is_horizon) // check the intersection
{
	(void)inter;
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
			//*inter += TILE_SIZE;
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

	printf("inter_x = %f, inter_y = %f\n", intersection_x, intersection_y);
	if (intersection_x < 0 || intersection_y < 0)
		return (1);
	if (angle >= 90 && angle <= 270)
		x = ceil(intersection_x) - 1;
	else
		x = floor(intersection_x);
	if (angle >= 0 && angle <= 180)
		y = ceil(intersection_y) - 1;
	else
		y = floor(intersection_y);
	if (y >= data->map.height || x >= data->map.width)
		return (1);
	if (data->map.file[y] && data->map.file[y][x])//?? x <= ft_strlen_double(data->map.file[y]) == data->map[y][x] ??
	{
		printf("map[%d][%d] = %c\n", y, x, data->map.file[y][x]);
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

	printf("horizontal: \n");
	//printf("playerx = %f, playery = %f\n", data->player.x, data->player.y);
	x_step = 1 / tan(angle  * (M_PI / 180));
	y_step = 1;
	first_step_x = x_step;
	first_step_y = y_step;
	first_step_y = data->player.y - ceil(data->player.y);
	first_step_x =  first_step_y / tan(angle * M_PI / 180);
	if (angle >= 0 && angle <= 180)
		first_step_x *= -1;
	else
		first_step_y *= -1;
	printf("first_step_x = %f\nfirst_step_y = %f\n", first_step_x, first_step_y);
	printf("xstep = %f, ystep = %f\n", x_step, y_step);
	intersection_y =  data->player.y + first_step_y;
	intersection_x = data->player.x + first_step_x;
	inter_check(angle, &intersection_y, &y_step, 1);
	if ((unit_circle(angle, 'y') && x_step > 0) || (!unit_circle(angle, 'y') && x_step < 0))
		x_step *= -1;
	printf("inter_x = %f, inter_y = %f\n", intersection_x, intersection_y);
	while (!is_wall(data, intersection_x, intersection_y, angle))
	{
		
		//printf("inter_x = %f, inter_y = %f\n", intersection_x, intersection_y);
		intersection_x += x_step;
		intersection_y += y_step;
	}
	printf("final : inter_x = %f, inter_y = %f\n", intersection_x, intersection_y);
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

	printf("\n\nvertical: \n");
	//printf("playerx = %f, playery = %f\n", data->player.x, data->player.y);
	x_step = 1;
	y_step = 1 * tan(angle  * (M_PI / 180));
	first_step_x = x_step;
	first_step_y = y_step;
	
	first_step_x = data->player.x - ceil(data->player.x);
	first_step_y = first_step_x * tan(angle * (M_PI / 180));
	if (angle >= 90 && angle <= 270)
		first_step_y *= -1;
	else
		first_step_x *= -1;
	intersection_x = data->player.x + first_step_x;
	intersection_y = data->player.y + first_step_y;
	printf("xstep = %f, ystep = %f\n", x_step, y_step);
	printf("first_step_x = %f\nfirst_step_y = %f\n", first_step_x, first_step_y);
	inter_check(angle, &intersection_x, &x_step, 0);
	if ((unit_circle(angle, 'x') && y_step > 0) || (!unit_circle(angle, 'x') && y_step < 0)) // check x_step value
 		 y_step *= -1;
	printf("inter_x = %f, inter_y = %f\n", intersection_x, intersection_y);
	while (!is_wall(data, intersection_x, intersection_y, angle))
	{
		printf("inter_x = %f, inter_y = %f\n", intersection_x, intersection_y);
		intersection_x += x_step;
		intersection_y += y_step;
	}
	
	printf("final : inter_x = %f, inter_y = %f\n\n", intersection_x, intersection_y);
	distance = sqrt(pow(intersection_x - data->player.x, 2) + pow(intersection_y - data->player.y, 2));
	//printf("distance = %f\n", distance);
	return (distance);
}

void	render_wall(t_data *data, int width)
{
	int height;
	//int	floor;
	int	ceiling;
	int	wall;
	
	height = 0;
	wall =  (data->win_height * 2) / (data->ray.distance + 1);//hauteru max / + la disatnce min
	printf("wall = %d\n\n", wall);
	//floor = (data->win_height - wall) / 2;
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

double	fix_angle(double angle)
{
	while (angle < 0)
		angle += 360;
	while (angle >= 360)
		angle -= 360;
	return(angle);
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
	//printf("PLAYER ANGLE = %f\n", data->player.angle);
	angle = data->player.angle - (data->player.fov / 2);

	//printf("angle ICI = %f\n", angle);
	horizontal_inter = 0;
	vertical_inter = 0;
	ray = 0;
	while (ray < data->win_width)
	{
		angle = fix_angle (angle);
		horizontal_inter = find_horizontal_intersection(data, angle);
		vertical_inter = find_vertical_intersection(data, angle);
		data->ray.distance = horizontal_inter;
		if (vertical_inter <= horizontal_inter)
			data->ray.distance = vertical_inter;
		data->ray.distance *= fabs(cos((angle - data->player.angle) * M_PI / 180));
		
		printf("ANGLE = %f\n", angle);
		printf("horizontale = %f\nverticale = %f\n", horizontal_inter, vertical_inter);
		//printf("distance = %f\n", data->ray.distance);
		render_wall(data, width);

		//printf("win_width = %d\n", data->win_width);
		angle = angle + (data->player.fov / (data->win_width - 1));
		//printf("APRES ANGLE = %f\n", angle);
	
		ray++;
		width++;//ray = width
		//printf("ray = %d\n\n", ray);
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
	//mlx_key_hook(data->win_ptr, &keybinding, data);
	//mlx_loop_hook(data->mlx_ptr, &game_loop, data);
	game_loop(data);
	mlx_loop(data->mlx_ptr);
}
