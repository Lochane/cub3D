/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 14:38:09 by lsouquie          #+#    #+#             */
/*   Updated: 2024/03/02 15:03:11 by lsouquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

void init_dir_n_s(t_data *data)
{
	if (data->map.spawn_side == 'N')
	{
		data->moves.planex = 0.66;
		data->moves.planey = 0;
		data->moves.dirx = 0;
		data->moves.diry = -1;
	}
	if (data->map.spawn_side == 'S')
	{
		data->moves.planex = -0.66;
		data->moves.planey = 0;
		data->moves.dirx = 0;
		data->moves.diry = 1;
	}
}

void init_dir_e_w(t_data *data)
{
	if (data->map.spawn_side == 'E')
	{
		data->moves.planex = 0;
		data->moves.planey = 0.66;
		data->moves.dirx = 1;
		data->moves.diry = 0;
	}
	if (data->map.spawn_side == 'E')
	{
		data->moves.planex = 0;
		data->moves.planey = -0.66;
		data->moves.dirx = -1;
		data->moves.diry = 0;
	}
}

void	init_moves(t_data *data)
{
	init_dir_e_w(data);
	init_dir_n_s(data);
	data->moves.posx = data->map.spawn_x;
	data->moves.posy = data->map.spawn_y;
	data->moves.movespeed = 0.2;
	data->moves.rotspeed = 0.06;
}