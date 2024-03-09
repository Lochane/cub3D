/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:57:37 by lsouquie          #+#    #+#             */
/*   Updated: 2024/03/09 20:51:25 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h" 

int	keybinding(int keysim, t_data *data)
{

		if (keysim == LEFT_KEY)
			data->player.angle -= 0.2f;
		if (keysim == RIGHT_KEY)
			data->player.angle += 0.2f;
		if (keysim == 'a')
		{
			data->player.x += sin(data->player.angle * (M_PI / 180)) * data->player.move_speed;
			data->player.y += cos(data->player.angle * (M_PI / 180)) * data->player.move_speed;
			data->map.spawn_x = data->player.x;
			data->map.spawn_y = data->player.y;
		}
		if (keysim == 'w')
		{
			data->player.x -= cos(data->player.angle * (M_PI / 180)) * data->player.move_speed;
			data->player.y += sin(data->player.angle * (M_PI / 180)) * data->player.move_speed;
			data->map.spawn_x = data->player.x;
			data->map.spawn_y = data->player.y;
		}
		if (keysim == 'd')
		{
			data->player.x -= sin(data->player.angle * (M_PI / 180)) * data->player.move_speed;
			data->player.y -= cos(data->player.angle * (M_PI / 180)) * data->player.move_speed;
			data->map.spawn_x = data->player.x;
			data->map.spawn_y = data->player.y;
		}
		if (keysim == 's')
		{
			data->player.x += cos(data->player.angle * (M_PI / 180)) * data->player.move_speed;
			data->player.y -= sin(data->player.angle * (M_PI / 180)) * data->player.move_speed;
			data->map.spawn_x = data->player.x;
			data->map.spawn_y = data->player.y;
		}
	return (0);
}