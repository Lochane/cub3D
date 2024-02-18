/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 16:38:14 by malancar          #+#    #+#             */
/*   Updated: 2024/02/18 21:13:15 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

void	raycasting(t_data *data)
{
	(void)data;
}

int		is_in_fov(t_data *data)
{
	double	angle;
	double	angle_max;
	
	angle = data->player.angle - (data->player.fov / 2);
	angle_max = data->player.angle + (data->player.fov / 2);
	
	printf("angle = %f, angle + fov = %f\n", angle,data->player.angle + (data->player.fov / 2));
	
	
	return (0);
}

void	print_ray(t_data *data, double angle)
{
	double	a;
	double	b;
	int	x;
	int	y;
	int center_x;
	int	center_y;

	center_x = data->player.x * data->map.square_size;
	center_y = data->player.y * data->map.square_size;
	center_x += data->map.square_size / 2;
	center_y += data->map.square_size / 2;
	x = center_x;
	y = center_y;
	
	// if (angle < 180)
	// 	a = tan( angle * (M_PI / 180));
	// else
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
	printf("angle = %f\n", angle);
	if (angle >= 0 && angle <= 90)
	{
		printf("0 -> 90\n");
		start_height = 0;
		end_height = center_y;
		start_width = center_x;
		end_width = data->win_width;
	}
	else if (angle >= 90 && angle <= 180)
	{
		printf("90 -> 180\n");
		start_height = 0;
		end_height = center_y;
		start_width = 0;
		end_width = center_x;
		
	}
	else if (angle >= 180 && angle <= 270)
	{
		printf("180 -> 270\n");
		start_height = center_y;
		end_height = data->win_height;
		start_width = 0;
		end_width = center_x;
	}
	else if (angle >= 270 && angle <= 360)
	{
		printf("270 -> 360\n");
		start_height = center_y;
		end_height = data->win_height;
		start_width = center_x;
		end_width = data->win_width;
	}
	int tmp = start_width;
	while (start_height < end_height)
	{
		tmp = start_width;
		while (tmp < end_width)
		{
			y = start_height;
			x = tmp;
			if (y - (a * x + b) >= -1 && y - (a * x + b) <= 1)
			{
				if ((y / data->map.square_size < data->map.height) && (x / data->map.square_size < data->map.width))
				{
					if (data->map.file[y / data->map.square_size][x / data->map.square_size] == '1')
						return;
					data->img.addr[start_height * data->win_width + tmp] = CYAN;
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
	
	angle = data->player.angle - (data->player.fov / 2);
	angle_max = data->player.angle + (data->player.fov / 2);
	printf("angle = %f, fov = %f, angle + fov = %f\n", angle, data->player.fov,data->player.angle + (data->player.fov / 2));
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
	int	width;
	int	height;

	i = 0;
	data->map.width = count_width(data);
	width = data->map.width;
	height = data->map.height;
	if (width > height)
		data->map.square_size = (data->win_width * ZOOM) / width;
	else
		data->map.square_size = data->win_height / height;

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
				print_square(data, data->img.width, data->img.width + data->map.square_size, data->img.height, data->img.height + data->map.square_size, RED);
			}
			else if (data->map.file[i][j] == '0')
		 	{
				//printf("map[%d][%d] = %c\n", i, j, data->map.file[i][j]);
				print_square(data, data->img.width, data->img.width + data->map.square_size, data->img.height, data->img.height + data->map.square_size, WHITE);
			}
			else if (data->map.file[i][j] == ' ')
			{
				//printf("map[%d][%d] = %c\n", i, j, data->map.file[i][j]);
				print_square(data, data->img.width, data->img.width + data->map.square_size, data->img.height, data->img.height + data->map.square_size, GREEN);
			}
			else if (data->map.file[i][j] == 'S' || data->map.file[i][j] == 'N' || data->map.file[i][j] == 'W'
						|| data->map.file[i][j] == 'E')
			{
				//printf("PERSONNAGE map[%d][%d] = %c\n", i, j, data->map.file[i][j]);
				print_square(data, data->img.width, data->img.width + data->map.square_size, data->img.height, data->img.height + data->map.square_size, PINK);
			}
	 		j++;
			data->img.width += data->map.square_size;
	 	}
	 	data->img.height += data->map.square_size;
	 	i++;
		//printf("map[i] = %s\n", data->map.file[i]);
	 }

}


void	game_loop(t_data *data)
{
	mini_map(data);
	print_all_rays(data);
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
