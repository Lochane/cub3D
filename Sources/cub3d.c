/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 16:38:14 by malancar          #+#    #+#             */
/*   Updated: 2024/02/15 17:36:08 by malancar         ###   ########.fr       */
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


void	print_tile(t_data *data, int img_height, int img_width)
{
	
	while (img_height < )
	{
		img_width = 0;
		while (img_width <)
		{
			data->img.addr[img_height * data->win_width + img_width] = RED;
			img_width++;
		}
		img_height++;
	}
	
}

void	mini_map(t_data *data)
{
	// int	i;
	// int	j;
	// double	a;
	// double	b;
	// double	x;
	// double	y;
	// double	x_min;
	// double	x_max;
	// double	y_max;
	// double	y_min;

	// a = data->player.angle;
	// b = 0;
	// y_min = -0.1;
	// x_min = -0.1;
	// y_max = 0.1;
	// x_max = 0.1;
	//a = 3;
	
	// y_min = -5;
	// x_min = -5;
	// y_max = 5;
	// x_max = 5;
	//i = 0;
	data->img.height = 0;
	// while (data->map.map_file[i])
	// {
	// 	data->img.width = 0;
	// 	j = 0;
	// 	while (data->map.map_file[i][j])
	// 	{
	// 		if (data->map.map_file[i][j] == '1')
	// 		{
	// 			print_tile(data);
	// 		}
	// 		if (data->map.map_file[i][j])
	// 			j++;
				
	// 	}
	// 	if (data->map.map_file[i][j])
	// 		i++;
	// }
	printf("img height = %d\n", data->img.height);
	print_tile(data, data->img.height, data->img.width);
	printf("img height = %d\n", data->img.height);


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