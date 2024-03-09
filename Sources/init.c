/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 14:57:39 by malancar          #+#    #+#             */
/*   Updated: 2024/03/09 15:12:17 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

void init_struct(t_data *data)
{
	data->mlx_ptr = NULL;
	data->win_ptr = NULL;
	// data->cub_file = NULL;
	data->map.width = 0;
	data->map.height = 0;
	data->map.spawn_y = 0;
	data->map.spawn_x = 0;
	data->map.spawn_side = 0;
	data->cub_file = NULL;
	data->texture.count = 0;
	data->file_weidht = 0;
	// data->win_width = SCREEN_WIDTH;
	// data->win_height = SCREEN_HEIGHT;
	
	// data->map.file = NULL;
	data->texture.ceiling_color = NULL;
	data->texture.floor_color = NULL;
	data->texture.no_path = NULL;
	data->texture.so_path = NULL;
	data->texture.we_path = NULL;
	data->texture.ea_path = NULL;
	// data->texture.texture_file= NULL;

}

void	init_window_and_image(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		error_msg("Error: mlx init fail\n", 0, data);
	mlx_get_screen_size(data->mlx_ptr, &data->win_width, &data->win_height);
	//printf("screen height = %d, screen width = %d\n", data->win_height, data->win_width);
	// data->win_height = 1000;
	// data->win_width = 1000;
	data->win_ptr = mlx_new_window(data->mlx_ptr, data->win_width,
			data->win_height, "Cub3D");
	if (!data->win_ptr)
	{
		free(data->mlx_ptr);
		error_msg("Error: window cannot be open\n", 0, data);
	}
	data->img.img = mlx_new_image(data->mlx_ptr, data->win_width, data->win_height);
	data->img.addr = (int *)mlx_get_data_addr(data->img.img,
			&data->img.bpp, &data->img.line_lenght, &data->img.endian);
	
}

void	init_player(t_data *data)
{
	//printf("spawn = %c\n", data->map.spawn_side);
	data->map.spawn_x += 0.5;
	data->map.spawn_y += 0.5;
	data->player.x = data->map.spawn_x;
	data->player.y = data->map.spawn_y;
	data->player.fov = 60;
	data->player.move_speed = 0.1;
	if (data->map.spawn_side == 'N')
		data->player.angle = 90;
	else if (data->map.spawn_side == 'E')
		data->player.angle = 0;
	else if (data->map.spawn_side == 'S')
		data->player.angle = 270;
	else if (data->map.spawn_side == 'W')
		data->player.angle = 180;
	
	// data->player.rotation_flag = ;
	// data->player.left_rotation = ;
	// data->player.right_rotation = ;
}

// void	init_game(t_data *data)
// {
	
// }
