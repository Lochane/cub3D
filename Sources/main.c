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
	parse_map(data);
	parse_color(data->texture.f_color, data);
}

void	cub3d(t_data *data)
{
	//INIT WINDOW
	init_window_and_image(data);
	load_texture(data);//init texture
	
	//START
	start_game(data);

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
	//print_map_info(data);
	cub3d(data);
}
