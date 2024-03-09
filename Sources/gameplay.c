/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:57:37 by lsouquie          #+#    #+#             */
/*   Updated: 2024/03/09 20:27:37 by lsouquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h" 

void	left_right(t_data *data, int keysim)
{
	if (keysim == 'a')
	{
		data->player.center_x += sin(data->player.angle * (M_PI / 180)) * \
			data->player.movespeed;
		data->player.center_y += cos(data->player.angle * (M_PI / 180)) * \
			data->player.movespeed;
		data->map.spawn_x = data->player.center_x;
		data->map.spawn_y = data->player.center_y;
	}
	if (keysim == 'd')
	{
		data->player.center_x -= sin(data->player.angle * (M_PI / 180)) * \
			data->player.movespeed;
		data->player.center_y -= cos(data->player.angle * (M_PI / 180)) * \
			data->player.movespeed;
		data->map.spawn_x = data->player.center_x;
		data->map.spawn_y = data->player.center_y;
	}
}

void	up_down(t_data *data, int keysim)
{
	if (keysim == 'w')
	{
		data->player.center_x -= cos(data->player.angle * (M_PI / 180)) * \
			data->player.movespeed;
		data->player.center_y += sin(data->player.angle * (M_PI / 180)) * \
			data->player.movespeed;
		data->map.spawn_x = data->player.center_x;
		data->map.spawn_y = data->player.center_y;
	}
	if (keysim == 's')
	{
		data->player.center_x += cos(data->player.angle * (M_PI / 180)) * \
			data->player.movespeed;
		data->player.center_y -= sin(data->player.angle * (M_PI / 180)) * \
			data->player.movespeed;
		data->map.spawn_x = data->player.center_x;
		data->map.spawn_y = data->player.center_y;
	}
}

int	keybinding(int keysim, t_data *data)
{
	if (keysim == LEFT_KEY)
		data->player.angle -= 0.1f;
	if (keysim == RIGHT_KEY)
		data->player.angle += 0.1f;
	up_down(data, keysim);
	left_right(data, keysim);
	return (0);
}
