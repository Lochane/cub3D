/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 18:20:29 by lsouquie          #+#    #+#             */
/*   Updated: 2024/04/04 17:56:51 by lsouquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

t_img	init_img(t_data *data, char *path)
{
	t_img	img;
	int		fd;

	fd = open(path, O_RDONLY);
	img.allow = 1;
	img.print = 0;
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
	data->texture.ea_texture.print = 1;
	data->texture.no_texture = init_img(data, data->texture.no_path);
	data->texture.no_texture.print = 1;
	data->texture.so_texture = init_img(data, data->texture.so_path);
	data->texture.we_texture = init_img(data, data->texture.we_path);
}
