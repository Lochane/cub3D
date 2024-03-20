/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 16:38:14 by malancar          #+#    #+#             */
/*   Updated: 2024/03/20 19:02:11 by lsouquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

int inter_check(double angle, double *step, int is_horizon)
{
	if (is_horizon)
	{
		if (!(angle > 0 && angle < 180))
			return (-1);
		*step *= -1;
	}
	else
	{
		if (!(angle > 90 && angle < 270))
			return (-1);
		*step *= -1;
	}
	return (1);
}

int unit_circle(double angle, char c)
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

	//printf("inter_x = %f, inter_y = %f\n", intersection_x, intersection_y);
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
	if (data->map.file[y] && x < (int)ft_strlen(data->map.file[y]) && data->map.file[y][x])//?? x <= ft_strlen_double(data->map.file[y]) == data->map[y][x] ??
	{
		if (data->map.file[y][x] == '1')
		{
			//printf("map[%d][%d] = %c\n", y, x, data->map.file[y][x]);
			return (1);
		}
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
	double	distance;

	//printf("horizontal: \n");
	//printf("playerx = %f, playery = %f\n", data->player.x, data->player.y);
	x_step = 1 / tan((angle)  * (M_PI / 180));
	y_step = 1;
	first_step_x = x_step;
	first_step_y = y_step;
	if (angle >= 0 && angle <= 180)
	{
		first_step_y = data->player.y - floor(data->player.y);
		first_step_y *= -1;
	}
	else
		first_step_y = data->player.y - ceil(data->player.y);
	first_step_x =  first_step_y * x_step;
	if (angle >= 0 && angle <= 180)
		first_step_x *= -1;
	else
		first_step_y *= -1;
	//printf("first_step_x = %f\nfirst_step_y = %f\n", first_step_x, first_step_y);
	//printf("xstep = %f, ystep = %f\n", x_step, y_step);
	intersection_y =  data->player.y + first_step_y;
	intersection_x = data->player.x + first_step_x;
	inter_check(angle, &y_step, 1);
	if ((unit_circle(angle, 'y') && x_step > 0) || (!unit_circle(angle, 'y') && x_step < 0))
		x_step *= -1;
	while (!is_wall(data, intersection_x, intersection_y, angle))
	{
		intersection_x += x_step;
		intersection_y += y_step;
	}
	//printf("final : inter_x = %f, inter_y = %f\n", intersection_x, intersection_y);
	distance = sqrt(pow(intersection_x - data->player.x, 2) + pow(intersection_y - data->player.y, 2));
	data->ray.h_inter_x = intersection_x;
	data->ray.h_inter_y = intersection_y;
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

	//printf("\n\nvertical: \n");
	//printf("playerx = %f, playery = %f\n", data->player.x, data->player.y);
	x_step = 1;
	y_step = tan((angle)  * (M_PI / 180));
	first_step_x = x_step;
	first_step_y = y_step;
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
	intersection_x = data->player.x + first_step_x;
	intersection_y = data->player.y + first_step_y;
	//printf("xstep = %f, ystep = %f\n", x_step, y_step);
	//printf("first_step_x = %f\nfirst_step_y = %f\n", first_step_x, first_step_y);
	inter_check(angle, &x_step, 0);
	if ((unit_circle(angle, 'x') && y_step > 0) || (!unit_circle(angle, 'x') && y_step < 0)) // check x_step value
 		 y_step *= -1;
	while (!is_wall(data, intersection_x, intersection_y, angle))
	{
		intersection_x += x_step;
		intersection_y += y_step;
	}
	//printf("final : inter_x = %f, inter_y = %f\n", intersection_x, intersection_y);
	distance = sqrt(pow(intersection_x - data->player.x, 2) + pow(intersection_y - data->player.y, 2));
	data->ray.v_inter_x = intersection_x;
	data->ray.v_inter_y = intersection_y;
	return (distance);
}

void	render_wall(t_data *data, int width)
{
	int height;
	int	wall_start;
	int	wall_end;
	int	wall;
	
	height = 0;
	wall =  (data->win_height * 2) / (data->ray.distance + 1);//hauteru max / + la disatnce min
	wall_start = (data->win_height - wall) / 2;
	wall_end = wall_start + wall;
	while (height < data->win_height)
	{
		if (height <= wall_start)
			data->img.addr[height * data->win_width + width] = BLACK;
		else if (height >= wall_start && height <= wall_end)
			data->img.addr[height * data->win_width + width] = render_texture(data, height, wall_start, wall_end);
		else
			data->img.addr[height * data->win_width + width] = BLACK;
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

void	ray_mm(t_data *data)
{
	int	x;
	int	y;
	int	step_x;
	int	step_y;
	int	position_x;
	int	position_y;
	int end_pos_x;
	int end_pos_y;
	int	err;
	int	e2;

	position_x = data->player.x * data->map.square_size;
	position_y = data->player.y * data->map.square_size;
	step_x = 1;
	step_y = 1;
//printf("inter_x = %d, inter_y = %d\n", data->ray.inter_points_x[i], data->ray.inter_points_y[i]);
	end_pos_x = data->ray.inter_x * data->map.square_size;
	end_pos_y = data->ray.inter_y * data->map.square_size;		
	// printf("end_pos_x = %d, end_pos_y = %d\n", end_pos_x, end_pos_y);
	// printf("interx = %f\n, intery = %f\n", data->ray.inter_x, data->ray.inter_y);
		x = abs(end_pos_x - position_x);
		y = abs(end_pos_y - position_y);
		if (position_x > end_pos_x)
			step_x = -1;
		if (position_y < end_pos_y)
			step_y = -1;
		err = x - y;
		while (position_x != end_pos_x && position_y != end_pos_y)
		{
			//printf("position_x = %d, position_y = %d\n", position_x, position_y);
			//printf("position_y *width + position_x = %d\n", position_y * data->win_width + position_x);
			data->img.addr[position_y * data->win_width + position_x] = WHITE;
			e2 = 2 * err;
			if (e2 > -y)
			{
				err -= y;
				position_x += step_x;
			}
			if (e2 < x)
			{
				err += x;
				position_y += step_y;
			}
	}
	
}

void	raycasting(t_data *data)
{
	double	angle;
	double	horizontal_inter;
	double	vertical_inter;
	int		width;

	width = 0;
	init_square_size(data);
	data->player.angle = fix_angle( data->player.angle);
	angle = data->player.angle - (data->player.fov / 2);
	horizontal_inter = 0;
	vertical_inter = 0;
	data->ray.inter_points_x = malloc(sizeof(double) * data->win_width);
	data->ray.inter_points_y = malloc(sizeof(double) * data->win_width);
	data->ray.angles = malloc(sizeof(double) * data->win_width);
	while (data->ray.ray_index < data->win_width)
	{
		angle = fix_angle (angle);
		//printf("\nangle = %f\n", angle);
		horizontal_inter = find_horizontal_intersection(data, angle);
		vertical_inter = find_vertical_intersection(data, angle);
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
		data->ray.distance *= fabs(cos((angle - data->player.angle) * M_PI / 180));
		//printf("inter_x = %f\n, inter_y = %f\n", data->ray.inter_x, data->ray.inter_y);
		//printf("horizontale = %f\nverticale = %f\n", horizontal_inter, vertical_inter);
		//printf("distance = %f\n", data->ray.distance);
		//ray_mm(data);
		angle = angle + (data->player.fov / (data->win_width - 1));
		data->ray.angles[data->ray.ray_index] = angle;
		data->ray.inter_points_x[data->ray.ray_index] = data->ray.inter_x;
		data->ray.inter_points_y[data->ray.ray_index] = data->ray.inter_y;
		render_wall(data, width);
		data->ray.ray_index++;
		width++;
		//printf("width = %d\n", data->win_width);
		//printf("ray = %d\n", ray);
	}
	data->ray.ray_index = 0;
	// while (ray < data->win_width)
	// {
	// 	printf("angle = %f\nwall = %f\n", data->ray.angles[ray], data->ray.inter_points_x[ray]);
	// 	ray++;
	// }
	//printf("ray = %d\n", ray);
}

int	game_loop(t_data *data)
{
	raycasting(data);
	mini_map(data);
	//display_ray_mm(data);
	//ray_mm(data); // work for one ray
	display_all_rays(data);//problem for angle = 90 and angle = 270
	//display_one_ray(data, 300, 4);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img, 0, 0);
	return (0);
}


void	start_game(t_data *data)
{
	mlx_hook(data->win_ptr, 33, 1L << 17, &quit_game, data);
	mlx_hook(data->win_ptr, KeyPress, KeyPressMask, &handle_keypress, data);
	mlx_hook(data->win_ptr, KeyRelease, KeyReleaseMask, &handle_keypress, data);

	mlx_key_hook(data->win_ptr, &keybinding, data);
	game_loop(data);
	
	mlx_loop(data->mlx_ptr);
}
