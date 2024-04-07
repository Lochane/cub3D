/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 14:57:39 by malancar          #+#    #+#             */
/*   Updated: 2024/04/06 01:57:09 by lsouquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

void	init_ref_texture(t_data *data)
{
	int	i;

	i = 0;
	data->texture.ref[0] = "NO";
	data->texture.ref[1] = "SO";
	data->texture.ref[2] = "WE";
	data->texture.ref[3] = "EA";
	data->texture.ref[4] = "F";
	data->texture.ref[5] = "C";
	data->texture.ref[6] = 0;
	ft_bzero(data->texture.texture_count, 30);
}

void	init_struct2(t_data *data)
{
	data->texture.no_path = NULL;
	data->texture.so_path = NULL;
	data->texture.we_path = NULL;
	data->texture.ea_path = NULL;
	data->texture.ea_texture.allow = 0;
	data->texture.no_texture.allow = 0;
	data->texture.we_texture.allow = 0;
	data->texture.so_texture.allow = 0;
	data->ray.ray_index = 0;
	data->ray.dirx = 0;
	data->ray.diry = 0;
	data->map.spawn_count = 0;
}

void	init_struct(t_data *data)
{
	data->mlx_ptr = NULL;
	data->win_ptr = NULL;
	data->map.file = NULL;
	data->map.width = 0;
	data->map.height = 0;
	data->map.spawn_y = 0;
	data->map.spawn_x = 0;
	data->map.spawn_side = 0;
	data->cub_file = NULL;
	data->texture.count = 0;
	data->file_weidht = 0;
	data->texture.ceiling_color = NULL;
	data->texture.floor_color = NULL;
	data->key_press = 0;
	init_struct2(data);
	init_ref_texture(data);
}

void	init_window_and_image(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		error_msg("Error\nmlx init fail\n", 0, data);
	load_texture(data);
	mlx_get_screen_size(data->mlx_ptr, &data->win_width, &data->win_height);
	data->win_ptr = mlx_new_window(data->mlx_ptr, data->win_width,
			data->win_height, "Cub3D");
	if (!data->win_ptr)
	{
		free(data->mlx_ptr);
		error_msg("Error\nwindow cannot be open\n", 0, data);
	}
	data->img.img = mlx_new_image(data->mlx_ptr, data->win_width, \
		data->win_height);
	if (!data->img.img)
	{
		free(data->mlx_ptr);
		//free(data->img.img);
		free_texture_path("test", 2, data);
		error_msg("Error\nimage cannot be open\n", 2, data);
	}
	data->img.addr = (int *)mlx_get_data_addr(data->img.img, \
			&data->img.bpp, &data->img.line_lenght, &data->img.endian);
}

void	init_player(t_data *data)
{
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
}