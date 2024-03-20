/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 14:57:39 by malancar          #+#    #+#             */
/*   Updated: 2024/03/20 15:57:00 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

void	init_struct(t_data *data)
{
	data->mlx_ptr = NULL;
	data->win_ptr = NULL;
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
	data->texture.no_path = NULL;
	data->texture.so_path = NULL;
	data->texture.we_path = NULL;
	data->texture.ea_path = NULL;
	data->key_press = 0;
}

void	init_window_and_image(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		error_msg("Error: mlx init fail\n", 0, data);
	mlx_get_screen_size(data->mlx_ptr, &data->win_width, &data->win_height);
	data->win_ptr = mlx_new_window(data->mlx_ptr, data->win_width,
			data->win_height, "Cub3D");
	if (!data->win_ptr)
	{
		free(data->mlx_ptr);
		error_msg("Error: window cannot be open\n", 0, data);
	}
	data->img.img = mlx_new_image(data->mlx_ptr, data->win_width, \
		data->win_height);
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

t_img	init_img(t_data *data, char *path)
{
	t_img	img;
	int		fd;

	fd = open(path, O_RDONLY);
	printf("%s\n", path);
	if (fd < 0)
		print_error_and_free("open", data);
	img.img = mlx_xpm_file_to_image(data->mlx_ptr, path, \
		&img.width, &img.height);
	if (!img.img)
		print_error_and_free("malloc", data);
	img.addr = (int *)mlx_get_data_addr(img.img, &img.bpp, \
		&img.line_lenght, &img.endian);
	close (fd);
	return (img);
}

void	load_texture(t_data *data)
{
	data->texture.ea_texture = init_img(data, data->texture.ea_path);
	data->texture.no_texture = init_img(data, data->texture.no_path);
	data->texture.so_texture = init_img(data, data->texture.so_path);
	data->texture.we_texture = init_img(data, data->texture.we_path);
}
