/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 13:28:56 by lsouquie          #+#    #+#             */
/*   Updated: 2024/02/08 13:30:17 by lsouquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"

int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		quit_game(data);
	return (0);
}

int	quit_game(t_data *data) // TODO voir pour les free
{
	if (data->win_ptr)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	if (data->mlx_ptr)
		mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	exit (0);
}