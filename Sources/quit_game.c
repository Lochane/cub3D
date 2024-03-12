/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 13:28:56 by lsouquie          #+#    #+#             */
/*   Updated: 2024/03/12 14:35:42 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

int	quit_game(t_data *data)
{
	free(data->texture.ea_path);
	free(data->texture.so_path);
	free(data->texture.no_path);
	free(data->texture.we_path);
	free(data->texture.ceiling_color);
	free(data->texture.floor_color);
	free_tab(data->map.file, data->map.height, data, 0);
	mlx_destroy_image(data->mlx_ptr, data->texture.ea_texture.img);
	mlx_destroy_image(data->mlx_ptr, data->texture.so_texture.img);
	mlx_destroy_image(data->mlx_ptr, data->texture.no_texture.img);
	mlx_destroy_image(data->mlx_ptr, data->texture.we_texture.img);
	mlx_destroy_image(data->mlx_ptr, data->img.img);
	if (data->win_ptr)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	if (data->mlx_ptr)
		mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	free(data);
	exit (0);
}
