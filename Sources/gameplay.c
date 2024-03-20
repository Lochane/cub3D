/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:57:37 by lsouquie          #+#    #+#             */
/*   Updated: 2024/03/20 17:57:34 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h" 

void	left_right(t_data *data, int keysim)
{
	if (keysim == 'a' && data->key_press == 1)
	{
		data->key_press = 1;
		data->player.x += sin(data->player.angle * (M_PI / 180)) * \
			data->player.move_speed;
		data->player.y += cos(data->player.angle * (M_PI / 180)) * \
			data->player.move_speed;
		data->map.spawn_x = data->player.x;
		data->map.spawn_y = data->player.y;
		game(data);
	}
	if (keysim == 'd' && data->key_press == 1)
	{
		data->player.x -= sin(data->player.angle * (M_PI / 180)) * \
			data->player.move_speed;
		data->player.y -= cos(data->player.angle * (M_PI / 180)) * \
			data->player.move_speed;
		data->map.spawn_x = data->player.x;
		data->map.spawn_y = data->player.y;
		game(data);
	}
}

void	up_down(t_data *data, int keysim)
{
	if (keysim == 's' && data->key_press == 1)
	{
		data->player.x -= cos(data->player.angle * (M_PI / 180)) * \
			data->player.move_speed * 2;
		data->player.y += sin(data->player.angle * (M_PI / 180)) * \
			data->player.move_speed * 2;
		data->map.spawn_x = data->player.x;
		data->map.spawn_y = data->player.y;
		game(data);
	}
	if (keysim == 'w' && data->key_press == 1)
	{
		data->player.x += cos(data->player.angle * (M_PI / 180)) * \
			data->player.move_speed * 2;
		data->player.y -= sin(data->player.angle * (M_PI / 180)) * \
			data->player.move_speed * 2;
		data->map.spawn_x = data->player.x;
		data->map.spawn_y = data->player.y;
		game(data);
	}
}

int	handle_keypress(int key_sym, t_data *data)
{
	if (key_sym == XK_Escape)
		quit_game(data);
	else if (key_sym == 'w')
		data->key_press = 1;
	else if (key_sym == 's') 
		data->key_press = 1;
	else if (key_sym == 'a')
		data->key_press = 1;
	else if (key_sym == 'd')
		data->key_press = 1;
	else if (key_sym == LEFT_KEY)
		data->key_press = 1;
	else if (key_sym == RIGHT_KEY)
		data->key_press = 1;
	return (0);
}

int	handle_key_release(int key_sym, t_data *data)
{
	if (key_sym == 'w')
		data->key_press = 0;
	else if (key_sym == 's') 
		data->key_press = 0;
	else if (key_sym == 'a')
		data->key_press = 0;
	else if (key_sym == 'd')
		data->key_press = 0;
	else if (key_sym == LEFT_KEY)
		data->key_press = 0;
	else if (key_sym == RIGHT_KEY)
		data->key_press = 0;
	return (0);
}

int	keybinding(int keysim, t_data *data)
{
	if (keysim == LEFT_KEY && data->key_press == 1)
		data->player.angle -= 2.;
	if (keysim == RIGHT_KEY && data->key_press == 1)
		data->player.angle += 2.;
	up_down(data, keysim);
	left_right(data, keysim);
	game(data);
	return (0);
}
