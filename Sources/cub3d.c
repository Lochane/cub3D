/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 16:38:14 by malancar          #+#    #+#             */
/*   Updated: 2024/03/20 15:42:40 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h" 

void	render_wall(t_data *data, int width)
{
	int	height;
	int	wall_start;
	int	wall_end;
	int	wall;

	height = 0;
	wall = (data->win_height * 2) / (data->ray.distance + 1);
	wall_start = (data->win_height - wall) / 2;
	wall_end = wall_start + wall;
	while (height < data->win_height)
	{
		if (height <= wall_start)
			data->img.addr[height * data->win_width + width] = BLUE;
		else if (height >= wall_start && height <= wall_end)
		{
			data->img.addr[height * data->win_width + width] = RED;
		}
		else
			data->img.addr[height * data->win_width + width] = GREEN;
		height++;
	}
}

int	render_game(t_data *data)
{
	raycasting(data);
	mini_map(data);
	display_all_rays(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img, 0, 0);
	return (0);
}

void	start_game(t_data *data)
{
	mlx_hook(data->win_ptr, 33, 1L << 17, &quit_game, data);
	mlx_hook(data->win_ptr, KeyPress, KeyPressMask, &handle_keypress, data);
	mlx_hook(data->win_ptr, KeyRelease, KeyReleaseMask, &handle_keypress, data);
	mlx_key_hook(data->win_ptr, &keybinding, data);
	render_game(data);
	mlx_loop(data->mlx_ptr);
}
