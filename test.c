/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 16:39:03 by malancar          #+#    #+#             */
/*   Updated: 2024/03/11 18:05:09 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


int inter_check(double angle, double *step, int is_horizon) // check the intersection
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

	printf("inter_x = %f, inter_y = %f\n", intersection_x, intersection_y);
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
	if (y >= data->map.height || x >= data->map.width)
		return (1);
	if (data->map.file[y] && x < (int)ft_strlen(data->map.file[y]) && data->map.file[y][x])//?? x <= ft_strlen_double(data->map.file[y]) == data->map[y][x] ??
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
	double	first_step_x;
	double	first_step_y;
	double	distance;

	printf("horizontal: \n");
	//printf("playerx = %f, playery = %f\n", data->player.x, data->player.y);
	x_step = 1 / tan((angle)  * (M_PI / 180));
	y_step = 1;
	first_step_x = x_step;
	first_step_y = y_step;
	first_step_y = data->player.y - ceil(data->player.y);
	first_step_x =  first_step_y * x_step;
	if (angle >= 0 && angle <= 180)
		first_step_x *= -1;
	else
		first_step_y *= -1;
	printf("first_step_x = %f\nfirst_step_y = %f\n", first_step_x, first_step_y);
	printf("xstep = %f, ystep = %f\n", x_step, y_step);
	data->ray.h_inter_y =  data->player.y + first_step_y;
	data->ray.h_inter_x = data->player.x + first_step_x;
	inter_check(angle, &y_step, 1);
	if ((unit_circle(angle, 'y') && x_step > 0) || (!unit_circle(angle, 'y') && x_step < 0))
		x_step *= -1;
	printf("inter_x = %f, inter_y = %f\n", data->ray.h_inter_x, data->ray.h_inter_y);
	while (!is_wall(data, data->ray.h_inter_x, data->ray.h_inter_y, angle))
	{
		
		//printf("inter_x = %f, inter_y = %f\n", data->ray.h_inter_x, data->ray.h_inter_y);
		data->ray.h_inter_x += x_step;
		data->ray.h_inter_y += y_step;
	}
	printf("final : inter_x = %f, inter_y = %f\n", data->ray.h_inter_x, data->ray.h_inter_y);
	distance = sqrt(pow(data->ray.h_inter_x - data->player.x, 2) + pow(data->ray.h_inter_y - data->player.y, 2));
	return (distance);
}

double		find_vertical_intersection(t_data *data, double angle)
{
	double	x_step;
	double	y_step;
	double	first_step_x;
	double	first_step_y;
	double	distance;

	printf("\n\nvertical: \n");
	//printf("playerx = %f, playery = %f\n", data->player.x, data->player.y);
	x_step = 1;
	y_step = tan((angle)  * (M_PI / 180));
	first_step_x = x_step;
	first_step_y = y_step;
	
	first_step_x = data->player.x - ceil(data->player.x);
	first_step_y = first_step_x * y_step;
	if (angle >= 90 && angle <= 270)
		first_step_y *= -1;
	else
		first_step_x *= -1;
	data->ray.h_inter_x = data->player.x + first_step_x;
	data->ray.h_inter_y = data->player.y + first_step_y;
	printf("xstep = %f, ystep = %f\n", x_step, y_step);
	printf("first_step_x = %f\nfirst_step_y = %f\n", first_step_x, first_step_y);
	inter_check(angle, &x_step, 0);
	if ((unit_circle(angle, 'x') && y_step > 0) || (!unit_circle(angle, 'x') && y_step < 0)) // check x_step value
 		 y_step *= -1;
	printf("inter_x = %f, inter_y = %f\n", data->ray.h_inter_x, data->ray.h_inter_y);
	while (!is_wall(data, data->ray.h_inter_x, data->ray.h_inter_y, angle))
	{
		//printf("inter_x = %f, inter_y = %f\n", intersection_x, data->ray.h_inter_y);
		data->ray.h_inter_x += x_step;
		data->ray.h_inter_x += y_step;
	}
	
	printf("final : inter_x = %f, inter_y = %f\n\n", data->ray.h_inter_x, data->ray.h_inter_y);
	distance = sqrt(pow(data->ray.h_inter_x - data->player.x, 2) + pow(data->ray.h_inter_y - data->player.y, 2));
	//printf("distance = %f\n", distance);
	return (distance);
}

// void	render_texture(t_data *data, int beg_wall, int end_wall, int height)
// {
// 	float	block_size;
// 	float 	ratio_x;
// 	float	ratio_y;

// 	if (data->ray.side == 0)
// 		ratio_x = 
// }

void	render_wall(t_data *data, int width)
{
	int height;
	int	ceiling;
	int	wall;
	
	height = 0;
	wall =  (data->win_height * 2) / (data->ray.distance + 1);//hauteru max / + la disatnce min
	ceiling = (data->win_height - wall) / 2;
	while (height < data->win_height)
	{
		if (height <= ceiling)
			data->img.addr[height * data->win_width + width] = BLUE;
		else if (height >= ceiling && height <= ceiling + wall)
			data->img.addr[height * data->win_width + width] = RED;
		else
			data->img.addr[height * data->win_width + width] = GREEN;
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
	int		ray;
	double	angle;
	double	distance_v_inter;
	double	distance_h_inter;
	int		width;
	
	width = 0;
	init_square_size(data);
	 data->player.angle = fix_angle( data->player.angle);
	angle = data->player.angle - (data->player.fov / 2);
	ray = 0;
	while (ray < data->win_width)
	{
		angle = fix_angle (angle);
		printf("\nangle = %f\n", angle);
		distance_h_inter = find_horizontal_intersection(data, angle);
		distance_v_inter= find_vertical_intersection(data, angle);
		data->ray.distance = distance_h_inter;
		data->ray.inter_x = data->ray.h_inter_x;
		data->ray.inter_y = data->ray.h_inter_y;
		if (distance_v_inter <= distance_h_inter)
		{
			data->ray.distance = distance_h_inter;
			data->ray.inter_x = data->ray.v_inter_x;
			data->ray.inter_y = data->ray.v_inter_y;
		}
		data->ray.distance *= fabs(cos((angle - data->player.angle) * M_PI / 180));
		printf("horizontale = %f\nverticale = %f\n", distance_h_inter, distance_v_inter);
		printf("distance = %f\n\n", data->ray.distance);
		render_wall(data, width);
		angle = angle + (data->player.fov / (data->win_width - 1));
		ray++;
		width++;
	}
}



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
	if (y >= data->map.height || x >= data->map.width)
		return (1);
	if (data->map.file[y] && x < (int)ft_strlen(data->map.file[y]) && data->map.file[y][x])//?? x <= ft_strlen_double(data->map.file[y]) == data->map[y][x] ??
	{
		printf("map[%d][%d] = %c\n", y, x, data->map.file[y][x]);
		if (data->map.file[y][x] == '1')
			return (1);
	}
	return (0);
}

void		find_horizontal_intersection(t_data *data, double angle, double *intersection_x, double *intersection_y)
{
	double	x_step;
	double	y_step;
	double	first_step_x;
	double	first_step_y;

	printf("horizontal: \n");
	printf("playerx = %f, playery = %f\n", data->player.x, data->player.y);
	x_step = 1 / tan((angle)  * (M_PI / 180));
	y_step = 1;
	first_step_x = x_step;
	first_step_y = y_step;
	first_step_y = data->player.y - ceil(data->player.y);
	first_step_x =  first_step_y * x_step;
	printf("first_step_x = %f\nfirst_step_y = %f\n", first_step_x, first_step_y);

	if (first_step_x > 0 && angle >= 0 && angle <= 180)
		first_step_x *= -1;
	else if (first_step_y > 0 && angle >= 180 && angle < 360)
		first_step_y *= -1;
	printf("first_step_x = %f\nfirst_step_y = %f\n", first_step_x, first_step_y);
	printf("xstep = %f, ystep = %f\n", x_step, y_step);
	*intersection_y =  data->player.y + first_step_y;
	*intersection_x = data->player.x + first_step_x;
	inter_check(angle, intersection_y, &x_step, 1);
	if ((unit_circle(angle, 'y') && x_step > 0) || (!unit_circle(angle, 'y') && x_step < 0))
		y_step *= -1;
	printf("inter_x = %f, inter_y = %f\n", *intersection_x, *intersection_y);
	while (!is_wall(data, *intersection_x, *intersection_y, angle))
	{
		
		//printf("inter_x = %f, inter_y = %f\n", *intersection_x, *intersection_y);
		*intersection_x += x_step;
		*intersection_y += y_step;
	}
	printf("final : inter_x = %f, inter_y = %f\n", *intersection_x, *intersection_y);
}

void		find_vertical_intersection(t_data *data, double angle, double *intersection_x, double *intersection_y)
{
	double	x_step;
	double	y_step;
	double	first_step_x;
	double	first_step_y;

	printf("\n\nvertical: \n");
	//printf("playerx = %f, playery = %f\n", data->player.x, data->player.y);
	x_step = 1;
	y_step = tan((angle)  * (M_PI / 180));
	first_step_x = x_step;
	first_step_y = y_step;
	
	first_step_x = data->player.x - ceil(data->player.x);
	first_step_y = first_step_x * y_step;
	if (first_step_x > 0 && angle >= 90 && angle <= 270)
		first_step_x *= -1;
	else if (first_step_y > 0 && ((angle >= 270 && angle < 360) || (angle >= 0 && angle <= 90)))
		first_step_y *= -1;
	*intersection_x = data->player.x + first_step_x;
	*intersection_y = data->player.y + first_step_y;
	printf("xstep = %f, ystep = %f\n", x_step, y_step);
	printf("first_step_x = %f\nfirst_step_y = %f\n", first_step_x, first_step_y);
	inter_check(angle, intersection_x, &y_step, 0);
	printf("xstep = %f, ystep = %f\n", x_step, y_step);

	if ((unit_circle(angle, 'x') && y_step > 0) || (!unit_circle(angle, 'x') && y_step < 0)) // check x_step value
 		 x_step *= -1;
	printf("inter_x = %f, inter_y = %f\n", *intersection_x, *intersection_y);
	while (!is_wall(data, *intersection_x, *intersection_y, angle))
	{
		printf("xstep = %f, ystep = %f\n", x_step, y_step);

		//printf("inter_x = %f, inter_y = %f\n", *intersection_x, *intersection_y);
		*intersection_x += x_step;
		*intersection_y += y_step;
	}
	
	printf("final : inter_x = %f, inter_y = %f\n\n", *intersection_x, *intersection_y);
	//printf("distance = %f\n", distance);
}

void	render_wall(t_data *data, int width)
{
	int height;
	//int	floor;
	int	ceiling;
	int	wall;
	
	height = 0;
	wall =  (data->win_height * 2) / (data->ray.distance + 1);//hauteru max / + la disatnce min
	//printf("wall = %d\n\n", wall);
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
	//printf("FIX \n");
	while (angle < 0)
		angle += 360;
	while (angle >= 360)
	{
		//printf("amgle ici = %f\n", angle);
		angle -= 360;
	}
	return(angle);
}

void	raycasting(t_data *data)
{
	int		ray;
	double	angle;
	double	inter_x;
	double	inter_y;
	int		width;
	double	distance_h;
	double	distance_v;
	
	width = 0;
	init_square_size(data);
	 data->player.angle = fix_angle( data->player.angle);
	angle = data->player.angle - (data->player.fov / 2);
	ray = 0;
	while (ray < data->win_width)
	{
		angle = fix_angle (angle);
		printf("\nangle = %f\n", angle);
		find_horizontal_intersection(data, angle, &inter_x, &inter_y);
		distance_h = sqrt(pow(inter_x - data->player.x, 2) + pow(inter_y - data->player.y, 2));
		data->ray.distance = distance_h;
		find_vertical_intersection(data, angle, &inter_x, &inter_y);
		distance_v = sqrt(pow(inter_x - data->player.x, 2) + pow(inter_y - data->player.y, 2));
		if (distance_v <= distance_h)
		{
			data->ray.distance = distance_h;
		}
		data->ray.distance *= fabs(cos((angle - data->player.angle) * M_PI / 180));
		printf("horizontale = %f\nverticale = %f\n", distance_h, distance_v);
		printf("distance = %f\n\n", data->ray.distance);
		render_wall(data, width);
		angle = angle + (data->player.fov / (data->win_width - 1));
		ray++;
		width++;
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
	
	game_loop(data);
	mlx_loop(data->mlx_ptr);
}
