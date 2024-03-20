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


void	is_file_valid(char *file_name, t_data *data)
{
	int	fd;

	if (ft_strncmp(".cub", &file_name[ft_strlen(file_name) -4], \
			ft_strlen(file_name)))
		error_msg("Error: expected [file.cub]\n", 0, data);
	fd = open(file_name, __O_DIRECTORY);
	if (fd > 0)
		print_error_and_free("open", data);
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		print_error_and_free("open", data);
	close (fd);
}

void	parsing(char *file_name, t_data *data)
{
	is_file_valid(file_name, data);
	file_to_tab(file_name, data);
	split_file(data);
	parse_map(data);
	data->map.floor_color = parse_color(data->texture.floor_color, data);
	data->map.ceiling_color = parse_color(data->texture.ceiling_color, data);
}

void	cub3d(t_data *data)
{
	init_window_and_image(data);
	init_player(data);
	mlx_hook(data->win_ptr, 33, 1L << 17, &quit_game, data);
	mlx_hook(data->win_ptr, KeyPress, KeyPressMask, &handle_keypress, data);
	mlx_hook(data->win_ptr, KeyRelease, KeyReleaseMask, &handle_keypress, data);
	mlx_key_hook(data->win_ptr, &keybinding, data);
	game(data);
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
	data->map.file[(int)data->map.spawn_y][(int)data->map.spawn_x] = '0';
	cub3d(data);
}