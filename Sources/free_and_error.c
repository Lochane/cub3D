/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:01:54 by malancar          #+#    #+#             */
/*   Updated: 2024/02/08 16:14:39 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

void	free_texture_path(char *msg, int tofree, t_data *data)
{
	free(data->texture.no_path);
	free(data->texture.so_path);
	free(data->texture.ea_path);
	free(data->texture.we_path);
	free(data->texture.c_color);
	free(data->texture.f_color);
	if (tofree == 0)
		error_msg(msg, 0, data);
	if (tofree == 1)
		error_msg(msg, 2, data);
}

void	*free_tab(char **res, size_t i, t_data *data, int allowfree)
{
	while (i-- > 0)
		free(res[i]);
	free(res);
	if (allowfree == 1)
		free(data);
	return (NULL);
}

void	error_msg(char *msg, int to_free, t_data *data)
{
	if (to_free == 2)
		free_tab(data->map.map_file, data->map.map_height, data, 0);
	if (to_free == 1)
		free_tab(data->cub_file, data->file_weidht, data, 0);
	free(data);
	write(2, msg, ft_strlen(msg));
	exit (0);
}
