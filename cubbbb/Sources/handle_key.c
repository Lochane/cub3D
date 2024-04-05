/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 18:18:41 by lsouquie          #+#    #+#             */
/*   Updated: 2024/03/22 18:25:00 by lsouquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

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
