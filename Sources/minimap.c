/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 14:14:06 by malancar          #+#    #+#             */
/*   Updated: 2024/03/18 00:49:51 by malancar         ###   ########.fr       */
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

void	print_ray(t_data *data, double angle)
{
	double	a;
	double	b;
	int	x;
	int	y;
	double center_x;
	double	center_y;

	center_x = data->map.spawn_x * data->map.square_size;
	center_y = data->map.spawn_y * data->map.square_size;
	center_x += data->map.square_size / 2;
	center_y += data->map.square_size / 2;
	
	x = center_x;
	y = center_y;

	a = -tan( angle * (M_PI / 180));
	b = y - (a * x);
	data->img.height = 0;
	int end_height = 0;
	int start_height = 0;
	int	start_width = 0;
	int end_width = 0;
	
	start_height = 0;
	end_height = data->win_height;
	start_width = 0;
	end_width = data->win_width;

	int tmp = start_width;
	while (start_height < end_height)
	{
		tmp = start_width;
		while (tmp < end_width)
		{
			y = start_height;
			x = tmp;
			// if (is_wall(data, a, b, x, y, start_height, tmp) == '1')
			// 	return;
			// else
				//data->img.addr[start_height * data->win_width + tmp] = WHITE;	
			if (y - (a * x + b) >= -1 && y - (a * x + b) <= 1)
			{
				if ((y / data->map.square_size < data->map.height) && (x / data->map.square_size < data->map.width))
				{
					//printf("map[%d][%d] = %c\n", y / data->map.square_size, x / data->map.square_size, data->map.file[y / data->map.square_size][x / data->map.square_size]);
					// if (data->map.file[y / data->map.square_size][x / data->map.square_size] == '1')
					// 	return;
					//printf("x = %d, y = %d\n", x, y);
					// if (y == data->ray.inter_y || x == data->ray.inter_x)
					// if (is_wall(data, x / data->map.square_size, y / data->map.square_size, angle))
					// {	
					// 	return;
					// }
					//printf("cc\n");
					data->img.addr[start_height * data->win_width + tmp] = WHITE;
					//printf("start_height * data->win_width + tmp = %d\n", start_height * data->win_width + tmp);
				}
			}
			tmp++;
		}
		start_height++;
	}
	
}

void	print_all_rays(t_data *data)
{
	double	angle;
	double	angle_max;
	
	//data->player.angle = 225;
	angle = data->player.angle - (data->player.fov / 2);
	angle_max = data->player.angle + (data->player.fov / 2);
	//angle = data->player.angle;
	//printf("angle = %f, fov = %f, angle + fov = %f\n", angle, data->player.fov,data->player.angle + (data->player.fov / 2));
	//angle_max = angle ;
	while (angle <= angle_max)
	{
		//printf("angle = %f\n", angle);
		print_ray(data, angle);
		angle++;
	}
}


void	print_square(t_data *data, int start_width, int end_width, int start_height, int end_height, int color)
{
	//c  = 0;
	int tmp = start_width;
	//printf("height= %d, win height = %d, width = %d, win width = %d\n", start_height, data->win_height, start_width, data->win_width);
	while (end_height <= data->win_height && start_height <= end_height)
	{
		tmp = start_width;
		while (end_width <= data->win_width && tmp <= end_width)
		{
			//printf("img width %d, win width = %d\n", data->img.width, data->win_width);
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
			//printf("i = %d, j = %d\nplayerx = %d, playery = %d\n", i, j, x, y);
	 		if (data->map.file[i][j] == '1')
			{
				//printf("sqauresize =%d\n", data->map.square_size);
				print_square(data, data->img.width, data->img.width + data->map.square_size, data->img.height, data->img.height + data->map.square_size, RED);
			}
			else if (data->map.file[i][j] == ' ')
			{
				//printf("map[%d][%d] = %c\n", i, j, data->map.file[i][j]);
				print_square(data, data->img.width, data->img.width + data->map.square_size, data->img.height, data->img.height + data->map.square_size, BLACK);
			}
			else
		 	{
				//printf("map[%d][%d] = %c\n", i, j, data->map.file[i][j]);
				print_square(data, data->img.width, data->img.width + data->map.square_size, data->img.height, data->img.height + data->map.square_size, GREEN);
			}
			if (i == y && j == x)
			{
				//printf("PERSONNAGE map[%d][%d] = %c\n", i, j, data->map.file[i][j]);
				//printf("i = %d, j = %d\nplayerx = %d, playery = %d\n", i, j, x, y);
				
				print_square(data, data->img.width, data->img.width + data->map.square_size, data->img.height, data->img.height + data->map.square_size, BLACK);
			}
	 		j++;
			//c = c + 100;
			data->img.width += data->map.square_size;
	 	}
	 	data->img.height += data->map.square_size;
	 	i++;
		//printf("map[i] = %s\n", data->map.file[i]);
	}
	// printf("x = %d, y = %d\n", x, y);
	
	// //print player :
	// double height;
	// double width;
	// height = data->player.x * data->map.square_size;
	// width = data->player.y * data->map.square_size;
	// printf("sqaure size = %d\n", data->map.square_size);
	// printf("height = %f, width = %f\n", height, width);
	// x = x / data->map.square_size;
	// y = y / data->map.square_size;
	// printf("x = %d, y = %d\n", x, y);
	// printf("playerx = %f, playery = %f\n", data->player.x, data->player.y);
	// if (data->map.file[y] && x < (int)ft_strlen(data->map.file[y]) && data->map.file[y][x] != 1)
	// {
	
	// 	print_square(data, width, width + data->map.square_size, height, height + data->map.square_size, BLACK);
	// }


}

void	display_one_ray(t_data *data, double angle, int wall_x, int wall_y)
{
	double	a;
	double	b;
	int	x;
	double	y;
	//int	y_save;
	
	(void)wall_y;
	x = data->player.x * data->map.square_size;
	//printf("mapwidth = %d, squaresize = %d\n", map_width, data->map.square_size);
	//printf("mapheight = %d\n", map_height);
	//printf("x = %d\n", x);
	//printf("angle = %f\n", angle);
	a = -tan(angle * (M_PI / 180));
	b = data->player.y * data->map.square_size - a * x;
	
	//printf("data->player.y * data->map.square_size = %f\n", data->player.y * data->map.square_size);
	//printf("wallx = %d, wally = %d\n", wall_x, wall_y);
	//printf("a = %f, b = %f\n", a, b);
	//y_save = data->player.y * data->map.square_size;
	while (x != wall_x)
	{
		y = a * x + b;
		// if (y >= wall_y )
		// {
		// 	y = wall_y;
		// 	break;
		// }
		// else if (y < 0 )
		// {
		// 	y = 0;
		// 	break;
		// }
		
		//printf("LA y = %d\n", y);
		// if (y < wall_y)
		// {
		// 	y_save = y;
		// 	//printf(" LA y_save = %d\n", y_save);
		// }
		//printf("y = %d\n", y);
		// if (y < 0 || y > wall_y)
		// {
		// 	//printf("x = %d, y = %d, ysave = %d\n", x, y, y_save);
		// 	printf("wallx = %d, wally = %d\n", wall_x, wall_y);
		// 	break ;
		// }
		if (y < 0 || y > data->win_height)
			return;
		//printf("data->ray.inter_points_x[i] = %f\n", floor(data->ray.inter_points_x[i]));
		//printf("y * data->win_width + x = %d\n", y * data->win_width + x);
		data->img.addr[(int)y * data->win_width + x] = WHITE;
		if (angle >= 90 && angle <= 270)
			x--;
		else
			x++;
	}
	//printf("ICI y_save = %d\n", y_save);
	// while (y_save != wall_y)
	// 	{
	// 		//printf("x = %d, y = %d\n", x, y);
	// 		//printf("cc\n");
	// 		printf("y_save = %d\n", y_save);

	// 		if (y_save > data->win_height)
	// 			return ;
	// 		printf("angle = %f\n", angle);
	// 		data->img.addr[y_save * data->win_width + x] = WHITE;
	// 		if (angle >= 0 && angle <= 180)
	// 			y_save--;
	// 		else
	// 			y_save++;
			
	// 	}
}

void	display_all_rays(t_data *data)
{
	int	i;
	
	i = 0;
	while (i < data->win_width)
	{
		//printf("angle = %f\nwallx = %f, wally = %f\n", data->ray.angles[i], data->ray.inter_points_x[i], data->ray.inter_points_y[i]);
		//printf("i = %d\n", i);
		display_one_ray(data, data->ray.angles[i], floor(data->ray.inter_points_x[i] * data->map.square_size), floor(data->ray.inter_points_y[i] * data->map.square_size));
		i++;
	}
	//display_one_ray(data, 90, floor(data->ray.inter_points_x[i]));
	free(data->ray.angles);
	free(data->ray.inter_points_x);
	free(data->ray.inter_points_y);
}


// void	display_ray_mm(t_data *data)
// {
// 	double	x;
// 	double	y;
// 	int	x_step;
// 	int		tmp_step;
// 	int		y_step;
// 	double	step;
// 	int	position_x;
// 	int	position_y;
// 	int end_pos_x;
// 	int end_pos_y;
// 	// int	err;
// 	// int	e2;
// 	int	i;
	
// 	i = 0;
// 	position_x = data->player.x * data->map.square_size;
// 	position_y = data->player.y * data->map.square_size;
// 	x_step = 1;
// 	y_step = 1;
// 	//printf("end_pos_x = %d, end_pos_y = %d\n", end_pos_x, end_pos_y);
// 	//printf("inter_x = %d, inter_y = %d\n", data->ray.inter_points_x[i], data->ray.inter_points_y[i]);
// 	//printf("inter_x = %f, inter_y = %f\n", data->ray.inter_points_x[i], data->ray.inter_points_y[i]);
// 	while (i < data->win_width)
// 	{
// 		//printf("angle = %f\n", data->ray.angles[i]);
// 		//printf("inter_x = %f, inter_y = %f\n", data->ray.inter_points_x[i], data->ray.inter_points_y[i]);
// 		end_pos_x = data->ray.inter_points_x[i] * data->map.square_size;
// 		end_pos_y = data->ray.inter_points_y[i] * data->map.square_size;
// 		//printf("ICI position_x = %d, positiony = %d\n", position_x, position_y);
// 		//printf("position_x = %d, positiony = %d\n", position_x, position_y);
// 		//printf("end_pos_x = %d, end_pos_y = %d\n", end_pos_x, end_pos_y);
// 		x = abs(position_x - end_pos_x);
// 		y = abs(position_y - end_pos_y);
// 		//printf("x = %f, y = %f\n", x, y);
// 		//err = x - y;
// 		x_step = 1;
		
// 		tmp_step = 1;
// 		step = x / y;
// 		int j = 0;
// 		while (position_x > end_pos_x || position_y < end_pos_y)
// 		{
// 			printf("end_pos_x = %d, end_pos_y = %d\n", end_pos_x, end_pos_y);
// 			printf("position_x = %d, positiony = %d\n", position_x, position_y);

// 			y_step = floor(tmp_step * step);

// 			// if (position_y > end_pos_y)
// 			// 	y_step *= -1;
// 			//printf("x / y = %f\n", x / y);
// 			//printf("step = %f, xstep = %d, ystep = %d\n", step, x_step, y_step);
// 			//y_step = 1;
// 			//printf("position_y * width + position_x = %d\n", position_y * data->win_width + position_x);
// 			while (y_step > 0)
// 			{
// 				printf("j = %d\n", j);
// 				printf("ystep = %d\n", y_step);
// 				printf("position_x = %d, positiony = %d\n", position_x, position_y);
// 				data->img.addr[position_y * data->win_width + position_x] = WHITE;
// 				if (position_y > end_pos_y)
// 				{
// 					break;
// 				}
				
// 				position_y += x_step;
// 				position_x -= x_step;
// 				y_step--;
// 				j++;
// 			}
// 			//e2 = 2 * err;
// 			// if (position_x > end_pos_x)
// 			// 	position_x -= x_step;
// 			// else
// 			// 	position_x += x_step;
// 			//position_y += y_step;
// 			tmp_step++;
// 		}
// 		i++;
		
// 	}
// 	free(data->ray.inter_points_x);
// 	free(data->ray.inter_points_y);
// 	free(data->ray.angles);
// }

void	display_ray_mm(t_data *data)
{
double	x;
	double	y;
	int	x_step;
	int		step2;
	int		y_step;
	double	step;
	int	position_x;
	int	position_y;
	int end_pos_x;
	int end_pos_y;
	// int	err;
	// int	e2;
	int	i;
	
	i = 0;
	position_x = data->player.x * data->map.square_size;
	position_y = data->player.y * data->map.square_size;
	x_step = 1;
	y_step = 1;
	while (i < data->win_width)
	{
		end_pos_x = data->ray.inter_points_x[i] * data->map.square_size;
		end_pos_y = data->ray.inter_points_y[i] * data->map.square_size;
		x = abs(position_x - end_pos_x);
		y = abs(position_y - end_pos_y);
		x_step = 1;
		y_step = 1;
		if (position_x > end_pos_x)
			x_step = -1;
		if (position_y > end_pos_y)
			y_step = -1;
		step2 = 1;
		step = x - y;
		while(position_x != end_pos_x || position_y != end_pos_y)
		{
			data->img.addr[position_y * data->win_width + position_x] = WHITE;
			step2 = 2 * step;
			if (step2 > -y)
			{
				step -= y;
				position_x += x_step;
			}
			if (step2 < x)
			{
				step += x;
				position_y += y_step;
			}
			
		}
		i++;
	}
}
