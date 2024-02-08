/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 17:13:33 by lsouquie          #+#    #+#             */
/*   Updated: 2024/02/08 18:10:13 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

int	flood_fill(int x, int y, char **map_file, t_data *data)
{
	if (y < 0 || x < 0|| map_file[x][y] == ' ' || x > data->map.map_height \
        || y > (int)ft_strlen(map_file[x]))
		return (0);
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

void	check_map(char **str, t_data *data)//TODO fonction free_tab_and_rexture
{
	while (tmp[i])
	{
		j = 0;
		while (tmp[i][j])
		{
			if (!is_char_valid(tmp[i][j]))
			{
				free_tab(tmp, data->map.map_height, data, 0);
				free_texture_path("Error:\n char not valid\n", 1, data);
			}
			if (tmp[i][j] == '0')
			{
				if (!flood_fill(i, j, tmp, data))
				{
					free_tab(tmp, data->map.map_height, data, 0);
					free_texture_path("Error:\nMap not valid\n", 1, data);
				}
			}
			j++;
		}
		i++;
	}
}

void	parse_map(t_data *data)
{
	int		i;
	int		j;
	char	**tmp;

	i = 0;
	j = 0;
	tmp = malloc(sizeof(char *) * (data->map.map_height + 1));
	if (!tmp)
		free_texture_path("Error:\nError malloc\n", 1, data);
	if (!copy_tab(tmp, data->map.map_file, data))
	{
		free_tab(tmp, data->map.map_height, data, 0);
		free_texture_path("Error:\nError malloc\n", 1, data);
	}
	found_spawn(tmp, data);
	
	free_tab(tmp, data->map.map_height, data, 0);
}

t_img init_img(t_data *data, char *path)
{
	t_img	img;
	int 	fd;
	
	fd = open(path, O_RDONLY);
	if (fd < 0)
		error_msg("Error:\nFile cannot be open\n", 2, data);
	close (fd);
	img.img = mlx_xpm_file_to_image(data->mlx_ptr, path, &img.width, &img.height);
	if (!img.img)
		error_msg("Error:\nMalloc\n", 0, data);
	img.addr = (int *)mlx_get_data_addr(img.img, &img.bpp, &img.linelenght, &img.endian);
	return (img);
}

void load_texture(t_data *data)
{
	data->texture.ea_texture = init_img(data, data->texture.ea_path);
	data->texture.no_texture = init_img(data, data->texture.no_path);
	data->texture.so_texture = init_img(data, data->texture.so_path);
	data->texture.we_texture = init_img(data, data->texture.we_path);
}
