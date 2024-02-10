/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:21:32 by malancar          #+#    #+#             */
/*   Updated: 2024/02/08 16:21:32 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

void	parsing(char *file_name, t_data *data)
{
	is_file_valid(file_name, data);
	file_to_tab(file_name, data);
	split_file(data);
	//load_texture(data);
	parse_map(data);
	parse_color(data->texture.c_color, data);
	parse_color(data->texture.f_color, data);
}

void	cub3d(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		error_msg("Error: mlx init fail\n", 0, data);
	data->win_ptr = mlx_new_window(data->mlx_ptr, data->win_weidht,
			data->win_height, "Cub3D");
	if (!data->win_ptr)
	{
		free(data->mlx_ptr);
		error_msg("Error: window cannot be open\n", 0, data);
	}
	mlx_hook(data->win_ptr, 33, 1L << 17, &quit_game, data);
	mlx_hook(data->win_ptr, KeyPress, KeyPressMask, &handle_keypress, data);


	//load_texture(data);

	mlx_loop(data->mlx_ptr);
}

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac != 2)
	{
		ft_putstr_fd("Argument expected : [map.cub]", 2);
		return (0);
	}
	data = malloc(sizeof(t_data));
	if (!data)
		return (0);
	init_struct(data);
	parsing(av[1], data);
	cub3d(data);
	//print_map_info(data);
}
