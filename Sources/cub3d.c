/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 16:38:14 by malancar          #+#    #+#             */
/*   Updated: 2024/02/12 19:08:30 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

void	raycasting(t_data *data)
{
	double	x1;
	double	x2;
	double	x3;
	double	x4;
	double	y1;
	double	y2;
	double	y3;
	double	y4;
	
	x1 = ;
	y1 = ;
	x2 = ;
	y2 = ;

	x3 = data->player.x;
	y3 = data->player.y;
	x4 = data->player.x + data->player.angle;
	y4 = data->player.y + data->player.angle;

	
}


void	game_loop(t_data *data)
{
	
	//delete image
	data->img.img = mlx_new_image(data->mlx_ptr, data->win_height, data->win_width);
	//hook the player (je sais pas ce que ca veut dire)
	//cast the rays
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data	`->img.img, 0, 0);
}

void	init_player(t_data *data)
{
	
	data->player.x = data->map.spawn_x;
	data->player.y = data->map.spawn_y;
	data->player.fov = 60; 
	if (data->map.spawn_side == 'N')
		data->player.angle = 0;
	else if (data->map.spawn_side == 'E')
		data->player.angle = 90;
	else if (data->map.spawn_side = "S")
		data->player.angle = 180;
	else if (data->map.spawn_side = "W")
		data->player.angle = 270;
	
	// data->player.rotation_flag = ;
	// data->player.left_rotation = ;
	// data->player.right_rotation = ;
}

void	start_game(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		error_msg("Error: mlx init fail\n", 0, data);
	init_player(data);
	mlx_hook(data->win_ptr, 33, 1L << 17, &quit_game, data);
	mlx_hook(data->win_ptr, KeyPress, KeyPressMask, &handle_keypress, data);
	
	
	
	game_loop(data);
	mlx_loop(data->mlx_ptr);
	//exit game
}