/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:57:37 by lsouquie          #+#    #+#             */
/*   Updated: 2024/03/19 18:42:21 by lsouquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h" 

int	check_dist(t_data *data, int keysim)
{
	double	new_x;
	double	new_y;

	if (keysim == 'd')
	{
		new_x = data->player.x - data->player.diry * 0.3;
		new_y = data->player.y + data->player.dirx * 0.3;
	}
	if (keysim == 'a')
	{
		new_x = data->player.x + data->player.diry * 0.3;
		new_y = data->player.y - data->player.dirx * 0.3;
	}
	if (data->map.file[(int)new_y][(int)new_x] != 1)
		return (1);
	return (0);
}

void	rotation_player(t_data *data, int keysim)
{
	double	old_dirx;
	double	radian_ngl;
	double	angle;

	old_dirx = data->player.dirx;
	if (keysim == LEFT_KEY && data->key_press == 1)
	{
		// data->player.angle -= 0.9f;
		angle = -5;
		radian_ngl = angle * M_PI / 180.0;
		data->player.dirx = data->player.dirx * cos(radian_ngl) - \
			data->player.diry * sin(radian_ngl);
		data->player.diry = old_dirx * sin(radian_ngl) + \
			data->player.diry * cos(radian_ngl);
	}
	if (keysim == RIGHT_KEY && data->key_press == 1)
	{
		// data->player.angle += 0.9f;
		angle = 5;
		radian_ngl = angle * M_PI / 180.0;
		data->player.dirx = data->player.dirx * cos(radian_ngl) - \
			data->player.diry * sin(radian_ngl);
		data->player.diry = old_dirx * sin(radian_ngl) + \
			data->player.diry * cos(radian_ngl);
	}

}

void	left_right(t_data *data, int keysim)
{
	double	new_x;
	double	new_y;

	if (keysim == 'd' && data->key_press == 1)
	{
		new_x = data->player.x - data->player.diry * 0.1;
		new_y = data->player.y + data->player.dirx * 0.1;
		game_loop(data);
	}
	if (keysim == 'a' && data->key_press == 1)
	{
		new_x = data->player.x + data->player.diry * 0.1;
		new_y = data->player.y - data->player.dirx * 0.1;
		game_loop(data);
	}
	if (check_dist(data, keysim) == 1)
	{
		data->player.x = new_x;
		data->player.y = new_y;
	}
}

void	up_down(t_data *data, int keysim)
{
	if (keysim == 's' && data->key_press == 1)
	{
		if (data->map.file[(int)data->player.y][(int)(data->player.x - data->player.dirx * 0.3)] == '0')
			data->player.x -= data->player.dirx * 0.1;
		if (data->map.file[(int)(data->player.y - data->player.diry * 0.3)][(int)data->player.x] == '0')
			data->player.y -= data->player.diry * 0.1;
		game_loop(data);
	}
	if (keysim == 'w' && data->key_press == 1)
	{
		if (data->map.file[(int)data->player.y][(int)(data->player.x + data->player.dirx * 0.3)] == '0')
			data->player.x += data->player.dirx * 0.1;
		if (data->map.file[(int)(data->player.y + data->player.diry * 0.3)][(int)data->player.x] == '0')
			data->player.y += data->player.diry * 0.1;
		game_loop(data);
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
	// printf("--0---------------------------- leak move -------------------------------------------\n");
	printf("%d\n", keysim);
	rotation_player(data, keysim);
	// left_right(data, keysim);
	up_down(data, keysim);
	game_loop(data);
	return (0);
}
