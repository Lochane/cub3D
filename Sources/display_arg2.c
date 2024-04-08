/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_arg2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 18:14:26 by lsouquie          #+#    #+#             */
/*   Updated: 2024/04/08 20:47:11 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

void	check_wrong_char(char **tmp, t_data *data)
{
	if (tmp[0])
	{
		if (ft_strcmp("NO", tmp[0]) != 0 && ft_strcmp("SO", tmp[0]) != 0 && \
				ft_strcmp("EA", tmp[0]) != 0 && ft_strcmp("WE", tmp[0]) != 0 && \
				ft_strcmp("F", tmp[0]) != 0 && ft_strcmp("C", tmp[0]) != 0 && \
					ft_strcmp("\n", tmp[0]) != 0)
		{
			free_tab(tmp, found_size(tmp, 0), data, 0);
			return (free_texture_path("Error\nWrong config\n", 1, data));
		}
	}
}

void	check_ref_tab(t_data *data)
{
	int	i;

	i = 0;
	while (data->texture.texture_count[i])
	{
		if (data->texture.texture_count[i] != 1)
			error_msg("Error\nWrong texture\n", 1, data);
		i++;
	}
}

void	count_texture(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data->cub_file[i])
	{
		j = 0;
		while (data->texture.ref[j])
		{
			if (ft_strncmp(data->texture.ref[j], data->cub_file[i], 2) == 0)
				data->texture.texture_count[j] += 1;
			else if (ft_strncmp(data->texture.ref[j], \
					data->cub_file[i], 1) == 0)
				data->texture.texture_count[j] += 1;
			j++;
		}
		i++;
	}
	check_ref_tab(data);
}

void	check_size(int i, t_data *data)
{
	int	j;
	int	count;

	j = 0;
	count = 0;
	data->map.height = found_size(data->cub_file, i);
	while (data->cub_file[i])
	{
		j = 0;
		while (data->cub_file[i][j])
		{
			count++;
			j++;
		}
		if (data->map.height >= 250 || count >= 250)
			free_texture_path("Error\nMap to big\n", 1, data);
		count = 0;
		i++;
	}
}
