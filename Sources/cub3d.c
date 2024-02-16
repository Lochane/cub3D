/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 16:38:14 by malancar          #+#    #+#             */
/*   Updated: 2024/02/16 19:34:18 by malancar         ###   ########.fr       */
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


void	print_tile(t_data *data, int color)
{
//	data->img.height = 0;
//	printf("a = %d, b = %d, c = %d, d= %d\n", a, b, c, d);
	while (data->img.height + 50 < data->win_height && data->img.height < data->img.height + 50)
	{
		data->img.width = 0;
		while (data->img.width + 50 < data->win_width && data->img.width  < data->img.width + 50)
		{
			//printf("img addr = %p\n", data->img.addr);
			data->img.addr[data->img.height * data->win_width + data->img.width] = color;
			data->img.width++;
		}
		data->img.height++;
	}
	
}

void	print_square(t_data *data, int a, int b, int c, int d, int color)
{
	//c  = 0;
	int tmp = a;
	//printf("img height= %d, win height = %d\n", data->img.height, data->win_height);
	while (d <= data->win_height && c <= d)
	{
		a = tmp;
		while(b <= data->win_width && a <= b)
		{
			//printf("img width %d, win width = %d\n", data->img.width, data->win_width);
			data->img.addr[c * data->win_width + a] = color;
			a++;
		}
		c++;
	}
}

void	mini_map(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	data->img.height = 0;
	while (data->map.map_file[i])
	{
	 	data->img.width = 0;
	 	j = 0;
	 	while (data->map.map_file[i][j])
	 	{
	 		if (data->map.map_file[i][j] == '1')
			{
				printf("map[%d][%d] = %c\n", i, j, data->map.map_file[i][j]);
				print_square(data, data->img.width, data->img.width + 50, data->img.height, data->img.height + 50, RED);
			}
			else if (data->map.map_file[i][j] == '0')
		 	{
				printf("map[%d][%d] = %c\n", i, j, data->map.map_file[i][j]);
				print_square(data, data->img.width, data->img.width + 50, data->img.height, data->img.height + 50, WHITE);
			}
			else if (data->map.map_file[i][j] == ' ')
			{
				printf("map[%d][%d] = %c\n", i, j, data->map.map_file[i][j]);
				print_square(data, data->img.width, data->img.width + 50, data->img.height, data->img.height + 50, GREEN);
			}
			else if (data->map.map_file[i][j] == 'S' || data->map.map_file[i][j] == 'N' || data->map.map_file[i][j] == 'W'
						|| data->map.map_file[i][j] == 'E')
			{
				printf("map[%d][%d] = %c\n", i, j, data->map.map_file[i][j]);
				print_square(data, data->img.width, data->img.width + 50, data->img.height, data->img.height + 50, PINK);
			}
	 		j++;
			data->img.width += 50;
	 	}
	 	data->img.height += 50;
	 	i++;
		//printf("map[i] = %s\n", data->map.map_file[i]);
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
