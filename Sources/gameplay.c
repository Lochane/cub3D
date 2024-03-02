/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:57:37 by lsouquie          #+#    #+#             */
/*   Updated: 2024/03/02 18:07:18 by lsouquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h" 

int	keybinding(int keysim, t_data *data)
{

		if (keysim == 'w')
		{
			if(data->map.file[(int)(data->moves.posx + data->moves.dirx * data->moves.movespeed)][(int)data->moves.posy] != 1)
				data->moves.posx += data->moves.dirx * data->moves.movespeed;
			if(data->map.file[(int)data->moves.posx][(int)(data->moves.posy + data->moves.diry * data->moves.movespeed)] != 1)
				 data->moves.posy += data->moves.diry * data->moves.movespeed;
		}
		if (keysim == 's')
		{
			if(data->map.file[(int)(data->moves.posx - data->moves.dirx * data->moves.movespeed)][(int)data->moves.posy] != 1)
				data->moves.posx -= data->moves.dirx * data->moves.movespeed;
			if(data->map.file[(int)data->moves.posx][(int)(data->moves.posy - data->moves.diry * data->moves.movespeed)] != 1)
				 data->moves.posy -= data->moves.diry * data->moves.movespeed;
		}
		if (keysim == 'd')
		{
			if(data->map.file[(int)(data->moves.posx + data->moves.dirx * data->moves.movespeed)][(int)data->moves.posy] != 1)
				data->moves.posx += data->moves.dirx * data->moves.movespeed;
			if(data->map.file[(int)data->moves.posx][(int)(data->moves.posy - data->moves.diry * data->moves.movespeed)] != 1)
				 data->moves.posy -= data->moves.diry * data->moves.movespeed;
			
		}
		if (keysim == 'a')
		{
			if(data->map.file[(int)(data->moves.posx - data->moves.dirx * data->moves.movespeed)][(int)data->moves.posy] != 1)
				data->moves.posx -= data->moves.dirx * data->moves.movespeed;
			if(data->map.file[(int)data->moves.posx][(int)(data->moves.posy + data->moves.diry * data->moves.movespeed)] != 1)
				 data->moves.posy += data->moves.diry * data->moves.movespeed;
		}
		if (keysim == LEFT_KEY)
		{
			data->moves.olddirx = data->moves.dirx;
			data->moves.dirx = data->moves.dirx * cos(data->moves.rotspeed) - data->moves.dirx * sin(data->moves.rotspeed);
			data->moves.diry = data->moves.olddirx * sin(data->moves.rotspeed) + data->moves.diry * cos(data->moves.rotspeed);
			data->moves.oldplanex = data->moves.planex;
			data->moves.planex = data->moves.planex * cos(data->moves.rotspeed) - data->moves.planey * sin(data->moves.rotspeed);
			data->moves.planey = data->moves.oldplanex * sin(data->moves.rotspeed) + data->moves.planey * cos(data->moves.rotspeed);
		}
		if (keysim == RIGHT_KEY)
		{
			data->moves.olddirx = data->moves.dirx;
			data->moves.dirx = data->moves.dirx * cos(-data->moves.rotspeed) - data->moves.dirx * sin(-data->moves.rotspeed);
			data->moves.diry = data->moves.olddirx * sin(-data->moves.rotspeed) + data->moves.diry * cos(-data->moves.rotspeed);
			data->moves.oldplanex = data->moves.planex;
			data->moves.planex = data->moves.planex * cos(-data->moves.rotspeed) - data->moves.planey * sin(-data->moves.rotspeed);
			data->moves.planey = data->moves.oldplanex * sin(-data->moves.rotspeed) + data->moves.planey * cos(-data->moves.rotspeed);
		}
	return (0);
}