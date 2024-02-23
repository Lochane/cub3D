/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 16:38:14 by malancar          #+#    #+#             */
/*   Updated: 2024/02/23 19:23:01 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"



int		hit_wall(t_data *data, float intersection_x, float intersection_y)
{
	int	x = 0;
	int	y = 0;

	if (intersection_x < 0 | intersection_y < 0)
		return (0);
	// x = floor(intersection_x / TILE_SIZE);//get the x position on the map
	// y = floor(intersection_y / TILE_SIZE);//get the y position in the map
	//printf("player x = %d\n", data->player.x);
	//x = floor(intersection_x / data->map.width);//get the x position on the map
	//y = floor(intersection_y / data->map.height);//get the y position in the map
	
	//x = interx  / (win_width / width(line actuel);
	int width = data->map.width = count_width(data);
	printf("data->win_width = %d, width = %d, intersection_x = %f\n", data->win_width, width, intersection_x);
	x = intersection_x / (data->win_width / width);
	printf("x = %d\n", x);
	y = intersection_y / (data->win_height / data->map.height);
	printf("y = %d\n", y);
	
	//printf("%f\n", (2040 / (ft_strlen(data->map.width[3])) * data->map.width  )
	//printf("inter x = %f, inter y = %f\n", intersection_x, intersection_y);
	//printf("x = %d, y = %d\n", x, y);
	//printf("height = %d, width = %d\n", data->map.height, data->map.width);
	if (y >= data->map.height || x >= data->map.width)
	{
		
		return (0); // if en dehors de la map
	}
	
	if (data->map.file[y] && data->map.file[y][x])//?? x <= ft_strlen_float(data->map.file[y]) == data->map[y][x] ??
	{
		//printf("map[%d][%d] = %c\n", y, x, data->map.file[y][x]);
		if (data->map.file[y][x] == '1')
		{
			
			return (1);
		}
	}
	return (0);
}

int		find_horizontal_intersection(t_data *data)
{
	float	x_step;
	float	y_step;
	float	intersection_x;
	float	intersection_y;

	intersection_y = 0;
	intersection_x = 0;

	int	pixel;
	double	distance;

	//printf("playerx = %d\n", data->player.x);
	//printf("playery = %d\n", data->player.y);
	data->player.x = data->player.x * data->map.square_size;
	data->player.y = data->player.y * data->map.square_size;
	data->player.x += data->map.square_size / 2;
	data->player.y += data->map.square_size / 2;
	//printf("playerx = %d\n", data->player.x);
	//printf("playery = %d\n", data->player.y);
	x_step = TILE_SIZE / tan(data->player.angle  * (M_PI / 180));
	y_step = TILE_SIZE;

	//mlx->ply->plyr_x + (h_y - mlx->ply->plyr_y) / tan(angl);

	intersection_y =  data->player.y;
	intersection_x = data->player.x + ((intersection_y - data->player.y) / tan(data->player.angle  * (M_PI / 180)));
	
	//printf("playerx = %d\n", data->player.x);
	//printf("playery = %d\n", data->player.y);
//	printf("intersectiony = %f\n", intersection_y);
//	printf("angle = %f\n", data->player.angle);
//	printf("tan(angle) %f\n", tan(data->player.angle  * (M_PI / 180)));
	// printf("inter x = %f, inter y = %f\n", intersection_x, intersection_y);
	
	//pas sur d'avoir compris :
	if (data->player.angle > 0 && data->player.angle < M_PI)
		pixel = intersection_y + TILE_SIZE;
	else
		pixel = y_step * -1;
	//
	
	// if ((unit_circle(angl, 'y') && x_step > 0) || (!unit_circle(angl, 'y') && x_step < 0)) // check x_step value
 	// 	 x_step *= -1;
	//check x_step value is in 
	while (!hit_wall(data, intersection_x, intersection_y - pixel))
	{
		
		intersection_x += x_step;
		intersection_y += y_step;
	}
	//quand un mur est touche, calcule la distance entre le joueur et l'intersection
	//pythagor: a^2 + b^2 = c^2
	//c = racine carre de a^2 + b^2;
	//c = distance
	distance = sqrt(pow(intersection_x - data->player.x, 2) + pow(intersection_y - data->player.y, 2));
	return (distance);
}

int		find_vertical_intersection(t_data *data)
{
	float	x_step;
	float	y_step;
	float	intersection_x;
	float	intersection_y;
	int	pixel;
	double	distance;

	//data->player.x = data->player.x * data->map.square_size;
	//data->player.y = data->player.y * data->map.square_size;
	//data->player.x += data->map.square_size / 2;
	//data->player.y += data->map.square_size / 2;

	y_step = TILE_SIZE / tan(data->player.angle  * (M_PI / 180));
	x_step = TILE_SIZE;
	
	
	intersection_y = 0;
	intersection_x = 0;
	intersection_x = data->player.x;
	printf("playerx = %d\n", data->player.x);
	intersection_y = data->player.y + (intersection_x - data->player.x) / tan(data->player.angle  * (M_PI / 180));
	
	//pas sur d'avoir compris :
	if (data->player.angle > 0 && data->player.angle < 180)
		pixel = intersection_y + TILE_SIZE;
	else
		pixel = y_step * -1;
	//
	
	// if ((unit_circle(angl, 'y') && x_step > 0) || (!unit_circle(angl, 'y') && x_step < 0)) // check x_step value
 	// 	 x_step *= -1;
	//check x_step value is in 

	while (hit_wall(data, intersection_x - pixel, intersection_y))
	{
		intersection_x += x_step;
		intersection_y += y_step;
	}
	//quand un mur est touche, calcule la distance entre le joueur et l'intersection
	//pythagor: a^2 + b^2 = c^2
	//c = racine carre de a^2 + b^2;
	//c = distance
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
	horizontal_inter = find_horizontal_intersection(data);
	printf("horizontal_inter = %f\n", horizontal_inter);
	vertical_inter = find_vertical_intersection(data);
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
	//mini_map(data);
	//print_all_rays(data);
	raycasting(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img, 0, 0);
}


void	start_game(t_data *data)
{
	init_player(data);
	mlx_hook(data->win_ptr, 33, 1L << 17, &quit_game, data);
	mlx_hook(data->win_ptr, KeyPress, KeyPressMask, &handle_keypress, data);
	
	game_loop(data);
	mlx_loop(data->mlx_ptr);
}
