/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 17:13:33 by lsouquie          #+#    #+#             */
/*   Updated: 2024/02/08 16:33:50 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

int	flood_fill(int x, int y, char **map_file, t_data *data)
{
	if (!map_file[x] || map_file[x][y] == 0 || map_file[x][y] == ' ')
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
	free_tab(tmp, data->map.map_height, data, 0);
}

void	parse_color(char *color, t_data *data)
{
	int		i;
	int		count;
	char	**tab;

	i = 0;
	count = 0;
	while (color[i])
	{
		if (color[i] == ',')
			count++;
		i++;
	}
	if (count != 2)
		free_texture_path("Error:\nColor not valid\n", 1, data);
	tab = ft_split(color, ',');
	if (!tab)
		free_texture_path("Error:\nColor not valid\n", 1, data);
	i = 0;
	while (tab[i])
	{	
		if ((ft_atoi(tab[i]) < 0 || ft_atoi(tab[i]) > 255) && !ft_isdigit(ft_atoi(tab[i])))
		{
			free_tab(tab, tab_size(tab), data, 0);
			free_texture_path("Error:\nColor not valid 1\n", 1, data);
		}
		i++;
	}
	if (i != 3)
	{
		free_tab(tab, tab_size(tab), data, 0);
		free_texture_path("Error:\nColor not valid 2\n", 1, data);
	}
	free_tab(tab, i, data, 0);
}

t_img ft_load_texture(t_data *data, char *path)
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
	data->texture.ea_texture = ft_load_texture(data, data->texture.ea_path);
	data->texture.no_texture = ft_load_texture(data, data->texture.no_path);
	data->texture.so_texture = ft_load_texture(data, data->texture.so_path);
	data->texture.we_texture = ft_load_texture(data, data->texture.we_path);
}
