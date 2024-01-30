/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 17:13:33 by lsouquie          #+#    #+#             */
/*   Updated: 2024/01/30 21:30:00 by lsouquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"

int	flood_fill(int x, int y, char **map_file, t_data *data)
{
	if(!map_file[x]|| map_file[x][y] == 0 || map_file[x][y] == ' ')
		error_msg("Error:\nWrong Map\n", 0, data);
	if (map_file[x][y] == '1' || map_file[x][y] == '2')
		return (1);
	if (map_file[x][y] == '0')
		map_file[x][y] = '2';
	if (!flood_fill(x +1, y, map_file, data))
		return (0);
	if (!flood_fill(x - 1, y, map_file, data))
		return (0);
	if (!flood_fill(x, y + 1, map_file, data))
		return (0);	
	if (!flood_fill(x, y - 1, map_file, data))
		return (0);
	return (1);
}

void parse_map(t_data *data)
{
	int i;
	int j;
	char **tmp;

	i = 0;
	j = 0;
	tmp = malloc(sizeof(char *) * (data->map.map_height + 1));
	if (!tmp)
		error_msg("Error:\n", 0, data);
	copy_tab(tmp, data->map.map_file, data);
	found_spawn(tmp, data);
	while(tmp[i])
	{
		j = 0;
		while(tmp[i][j])
		{
			validate_chars(data, tmp[i][j]);
			if(tmp[i][j] == '0')
			{
				if (!flood_fill(i, j, tmp, data))
					error_msg("Error:\nWrong Map\n", 0, data);
			}
			j++;
		}
		i++;
	}
}

void parse_color(char *color, t_data *data)
{
	int i;
	int count;
	char	**tab;

	i = 0;
	count = 0;
	while(color[i])
	{
		if (color[i] == ',')
			count++;
		i++;
	}
	if (count != 2)
		error_msg("3Error:\nWrong colors\n", 0, data);
	tab = ft_split(color, ',');
	i = 0;
	while(tab[i])
	{	
		if (ft_atoi(tab[i]) < 0 || ft_atoi(tab[i]) > 255)
			error_msg("1Error:\nWrong colors\n", 0, data);	
		i++;
	}
	if (i != 3)
		error_msg("2Error:\nWrong colors\n", 0, data);
}

void load_texture(t_data *data)
{
	data->texture.ea_texture.img = mlx_xpm_file_to_image(data->mlx_ptr, data->texture.ea_path, &data->texture.ea_texture.width, &data->texture.ea_texture.height);
	if (!data->texture.ea_texture.img)
		error_msg("Error:\nWrong texture\n", 0, data);
	data->texture.ea_texture.addr = mlx_get_data_addr(data->texture.ea_texture.img, data->texture.ea_texture.bpp, (data->texture.ea_texture.linelenght / 4), data->texture.ea_texture.endian);
	data->texture.so_texture.img = mlx_xpm_file_to_image(data->mlx_ptr, data->texture.so_path, &data->texture.so_texture.width, &data->texture.so_texture.height);
	if (!data->texture.so_texture.img)
		error_msg("Error:\nWrong texture\n", 0, data);
	data->texture.so_texture.addr = mlx_get_data_addr(data->texture.so_texture.img, data->texture.so_texture.bpp, (data->texture.so_texture.linelenght / 4), data->texture.so_texture.endian);
	data->texture.no_texture.img = mlx_xpm_file_to_image(data->mlx_ptr, data->texture.no_path, &data->texture.no_texture.width, &data->texture.no_texture.height);
	if (!data->texture.no_texture.img)
		error_msg("Error:\nWrong texture\n", 0, data);
	data->texture.no_texture.addr = mlx_get_data_addr(data->texture.no_texture.img, data->texture.no_texture.bpp, (data->texture.no_texture.linelenght / 4), data->texture.no_texture.endian);
	data->texture.we_texture.img = mlx_xpm_file_to_image(data->mlx_ptr, data->texture.we_path, &data->texture.we_texture.width, &data->texture.we_texture.height);
	if (!data->texture.we_texture.img)
		error_msg("Error:\nWrong texture\n", 0, data);
	data->texture.we_texture.addr = mlx_get_data_addr(data->texture.we_texture.img, data->texture.we_texture.bpp, (data->texture.we_texture.linelenght / 4), data->texture.we_texture.endian);
	
}