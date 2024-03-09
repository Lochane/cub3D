/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:57:37 by lsouquie          #+#    #+#             */
/*   Updated: 2024/03/09 14:48:16 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h" 

int	keybinding(int keysim, t_data *data)
{

		if (keysim == LEFT_KEY)
			data->player.angle -= 0.1f;
		if (keysim == RIGHT_KEY)
			data->player.angle += 0.1f;
		if (keysim == 'a')
		{
			data->player.center_x += sin(data->player.angle * (M_PI / 180)) * data->player.move_speed;
			data->player.center_y += cos(data->player.angle * (M_PI / 180)) * data->player.move_speed;
			data->map.spawn_x = data->player.center_x;
			data->map.spawn_y = data->player.center_y;
		}
		if (keysim == 'w')
		{
			data->player.center_x -= cos(data->player.angle * (M_PI / 180)) * data->player.move_speed;
			data->player.center_y += sin(data->player.angle * (M_PI / 180)) * data->player.move_speed;
			data->map.spawn_x = data->player.center_x;
			data->map.spawn_y = data->player.center_y;
		}
		if (keysim == 'd')
		{
			data->player.center_x -= sin(data->player.angle * (M_PI / 180)) * data->player.move_speed;
			data->player.center_y -= cos(data->player.angle * (M_PI / 180)) * data->player.move_speed;
			data->map.spawn_x = data->player.center_x;
			data->map.spawn_y = data->player.center_y;
		}
		if (keysim == 's')
		{
			data->player.center_x += cos(data->player.angle * (M_PI / 180)) * data->player.move_speed;
			data->player.center_y -= sin(data->player.angle * (M_PI / 180)) * data->player.move_speed;
			data->map.spawn_x = data->player.center_x;
			data->map.spawn_y = data->player.center_y;
		}
	return (0);
}