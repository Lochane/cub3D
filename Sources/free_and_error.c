/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:01:54 by malancar          #+#    #+#             */
/*   Updated: 2024/03/15 17:30:12 by lsouquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

void	free_texture_path(char *msg, int to_free, t_data *data)
{
	free(data->texture.no_path);
	free(data->texture.so_path);
	free(data->texture.ea_path);
	free(data->texture.we_path);
	free(data->texture.ceiling_color);
	free(data->texture.floor_color);
	if (to_free == 0)
		error_msg(msg, 0, data);
	if (to_free == 1)
		error_msg(msg, 1, data);
}

void	*free_tab(char **res, size_t i, t_data *data, int allow_free)
{
	while (i-- > 0)
		free(res[i]);
	free(res);
	if (allow_free == 1)
		free(data);
	return (NULL);
}

void	error_msg(char *msg, int to_free, t_data *data)
{
	if (to_free == 2)
		free_tab(data->map.file, data->map.height, data, 0);
	if (to_free == 1)
		free_tab(data->cub_file, data->file_weidht, data, 0);
	free(data);
	write(2, msg, ft_strlen(msg));
	exit (0);
}

void	print_error_and_free(char *error, t_data *data)
{
	perror(error);
	if (data->texture.ea_texture.allow == 1)
		mlx_destroy_image(data->mlx_ptr, data->texture.ea_texture.img);
	if (data->texture.so_texture.allow == 1)
		mlx_destroy_image(data->mlx_ptr, data->texture.so_texture.img);
	if (data->texture.no_texture.allow == 1)
		mlx_destroy_image(data->mlx_ptr, data->texture.no_texture.img);
	if (data->texture.we_texture.allow == 1)
		mlx_destroy_image(data->mlx_ptr, data->texture.we_texture.img);
	free_texture_path(NULL, 4, data);
	if (data->map.file)
		free_tab(data->map.file, data->map.height, data, 0);
	if (data->mlx_ptr)
	{
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
	}
	free(data);
	exit(EXIT_FAILURE);
}

void	split_free_error(t_data *data, int to_free)
{
	free_texture_path(NULL, 4, data);
	error_msg("Error:\n Erreur Malloc", 1, data);
	if (to_free == 1)
		free_tab(data->map.file, tab_size(data->map.file), data, 0);
}
