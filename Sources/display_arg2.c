/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_arg2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 18:14:26 by lsouquie          #+#    #+#             */
/*   Updated: 2024/03/23 18:01:35 by lsouquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

void	check_ref_tab(t_data *data)
{
	int	i;

	i = 0;
	while (data->texture.texture_count[i])
	{
		if (data->texture.texture_count[i] != 1)
			error_msg("Error:\nWrong texture\n", 1, data);
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
