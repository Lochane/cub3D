/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:57:37 by lsouquie          #+#    #+#             */
/*   Updated: 2024/04/07 20:36:03 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h" 

void	check_wall(t_data *data, double player_x, double player_y)
{
	if (data->map.file[(int)(player_y)][(int)(data->player.x)] != '1')
	{
		data->player.y = player_y;
		data->map.spawn_y = player_y;
	}
	if (data->map.file[(int)(data->player.y)][(int)(player_x)] != '1')
	{
		data->player.x = player_x;
		data->map.spawn_x = player_x;
	}
}

void	left_right(t_data *data, int keysim)
{
	double	player_x;
	double	player_y;

	player_x = data->player.x;
	player_y = data->player.y;
	if (keysim == 'd' && data->key_press == 1)
	{
		data->key_press = 1;
		player_x += sin(data->player.angle * (M_PI / 180)) * \
			data->player.move_speed;
		player_y += cos(data->player.angle * (M_PI / 180)) * \
			data->player.move_speed;
		check_wall(data, player_x, player_y);
	}
	if (keysim == 'a' && data->key_press == 1)
	{
		player_x -= sin(data->player.angle * (M_PI / 180)) * \
			data->player.move_speed;
		player_y -= cos(data->player.angle * (M_PI / 180)) * \
			data->player.move_speed;
		check_wall(data, player_x, player_y);
	}
}

void	up_down(t_data *data, int keysim)
{
	double	player_x;
	double	player_y;

	player_x = data->player.x;
	player_y = data->player.y;
	if (keysim == 's' && data->key_press == 1)
	{
		player_x -= cos(data->player.angle * (M_PI / 180)) * \
			data->player.move_speed * 2;
		player_y += sin(data->player.angle * (M_PI / 180)) * \
			data->player.move_speed * 2;
		check_wall(data, player_x, player_y);
	}
	if (keysim == 'w' && data->key_press == 1)
	{
			player_x += cos(data->player.angle * (M_PI / 180)) * \
				data->player.move_speed * 2;
			player_y -= sin(data->player.angle * (M_PI / 180)) * \
				data->player.move_speed * 2;
		check_wall(data, player_x, player_y);
	}
}

int	keybinding(int keysim, t_data *data)
{
	if (keysim == LEFT_KEY && data->key_press == 1)
		data->player.angle += 2.;
	if (keysim == RIGHT_KEY && data->key_press == 1)
		data->player.angle -= 2.;
	left_right(data, keysim);
	up_down(data, keysim);
	left_right(data, keysim);
	game(data);
	return (0);
}
