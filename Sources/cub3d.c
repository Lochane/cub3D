/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalvie <lcalvie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 16:38:14 by malancar          #+#    #+#             */
/*   Updated: 2024/02/17 13:50:51 by lcalvie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

void	raycasting(t_data *data)
{
	(void)data;
	// double	x1;
	// double	x2;
	// double	x3;
	// double	x4;
	// double	y1;
	// double	y2;
	// double	y3;
	// double	y4;
	
	// x1 = ;
	// y1 = ;
	// x2 = ;
	// y2 = ;

	// x3 = data->player.x;
	// y3 = data->player.y;
	// x4 = data->player.x + data->player.angle;
	// y4 = data->player.y + data->player.angle;

	// double	den;
	// double	t;
	// double	u;
	// den = ((x1 - x2) * (y3 -y4)) - ((y1 - y2) * (x3 - x4));
	// if (den == 0)
	// 	return (0);//line parallele
	// t = (((x1 - x3) * (y3 - y4)) - ((y1 - y3) * (x3 - x4))) / den;
	// u = - (((x1 - x2) * (y1 - y3)) * ((y1 - y2) * (x1 - x3))) / den;
	// if (t > 0 && t < 1 && u > 0)
	// 	return (1);//intersection point
	// else
	// 	return (0);
}


// void	print_ray(t_data *data)
// {
// 	double	a;
// 	double	b;

// 	//y = ax + b;
// 	//a = tangente de l'angle
// 	//b = position de depart
// 	//b = playery - tan(angle) * playerx
// 	//x et y en pixel
	
// 	a = tan(data->player.angle);
// 	b = data->player.y - (a * data->player.x);
// }



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
	int	square_size;
	int	width;
	int	height;

	i = 0;
	data->map.width = count_width(data);
	width = data->map.width;
	height = data->map.height;
	if (width > height)
		square_size = (data->win_width * 0.25) / width;
	else
		square_size = data->win_height / height;
	
	//printf("width = %d\n", data->map.width);
	//printf("width = %d, height = %d\n", width, height);
	printf("square size = %d\n", square_size);
	data->img.height = 0;
	while (data->map.file[i])
	{
	 	data->img.width = 0;
	 	j = 0;
	 	while (data->map.file[i][j])
	 	{
	 		if (data->map.file[i][j] == '1')
			{
				//printf("map[%d][%d] = %c\n", i, j, data->map.file[i][j]);
				print_square(data, data->img.width, data->img.width + square_size, data->img.height, data->img.height + square_size, RED);
			}
			else if (data->map.file[i][j] == '0')
		 	{
				//printf("map[%d][%d] = %c\n", i, j, data->map.file[i][j]);
				print_square(data, data->img.width, data->img.width + square_size, data->img.height, data->img.height + square_size, WHITE);
			}
			else if (data->map.file[i][j] == ' ')
			{
				//printf("map[%d][%d] = %c\n", i, j, data->map.file[i][j]);
				print_square(data, data->img.width, data->img.width + square_size, data->img.height, data->img.height + square_size, GREEN);
			}
			else if (data->map.file[i][j] == 'S' || data->map.file[i][j] == 'N' || data->map.file[i][j] == 'W'
						|| data->map.file[i][j] == 'E')
			{
				//printf("PERSONNAGE map[%d][%d] = %c\n", i, j, data->map.file[i][j]);
				print_square(data, data->img.width, data->img.width + square_size, data->img.height, data->img.height + square_size, PINK);
			}
	 		j++;
			data->img.width += square_size;
	 	}
	 	data->img.height += square_size;
	 	i++;
		//printf("map[i] = %s\n", data->map.file[i]);
	 }

}


void	game_loop(t_data *data)
{
	
	//delete image
	//data->img.img = mlx_new_image(data->mlx_ptr, data->win_height, data->win_width);
	//hook the player (je sais pas ce que ca veut dire)
	//cast the rays
	mini_map(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img, 0, 0);
}


void	start_game(t_data *data)
{
	init_player(data);
	mlx_hook(data->win_ptr, 33, 1L << 17, &quit_game, data);
	mlx_hook(data->win_ptr, KeyPress, KeyPressMask, &handle_keypress, data);
	
	game_loop(data);
	mlx_loop(data->mlx_ptr);
	//exit game
}
