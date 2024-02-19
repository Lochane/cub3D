/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalvie <lcalvie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 17:13:33 by lsouquie          #+#    #+#             */
/*   Updated: 2024/02/17 13:11:58 by lcalvie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

int	flood_fill(int x, int y, char **file, t_data *data)
{
	if (y < 0 || x < 0|| file[x][y] == ' ' || x > data->map.height \
        || y > (int)ft_strlen(file[x]) || !file[x][y])
		return (0);
	if (file[x][y] == '1' || file[x][y] == '2')
		return (1);
	if (file[x][y] == '0')
		file[x][y] = '2';
	if (!flood_fill(x +1, y, file, data))
		return (0);
	if (!flood_fill(x - 1, y, file, data))
		return (0);
	if (!flood_fill(x, y + 1, file, data))
		return (0);
	if (!flood_fill(x, y - 1, file, data))
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
	tmp = malloc(sizeof(char *) * (data->map.height + 1));
	if (!tmp)
		free_texture_path("Error malloc\n", 1, data);
	if (!copy_tab(tmp, data->map.file, data))
	{
		free_tab(tmp, data->map.height, data, 0);
		free_texture_path("Error: malloc\n", 1, data);
	}
	found_spawn(tmp, data);
	while (tmp[i])
	{
		j = 0;
		while (tmp[i][j])
		{
			if (!is_char_valid(tmp[i][j]))
			{
				free_tab(tmp, data->map.height, data, 0);
				free_texture_path("Error: char not valid\n", 1, data);
			}
			if (tmp[i][j] == '0')
			{
				if (!flood_fill(i, j, tmp, data))
				{
					free_tab(tmp, data->map.height, data, 0);
					free_texture_path("Error: Map not valid\n", 1, data);
				}
			}
			j++;
		}
		i++;
	}
	free_tab(tmp, data->map.height, data, 0);
}

t_img init_img(t_data *data, char *path)
{
	t_img	img;
	int 	fd;
	
	fd = open(path, O_RDONLY);
	printf("%s\n", path);
	if (fd < 0)
		print_error_and_free("open", data);
	img.img = mlx_xpm_file_to_image(data->mlx_ptr, path, &img.width, &img.height);
	if (!img.img)
		print_error_and_free("malloc", data);
	img.addr = (int *)mlx_get_data_addr(img.img, &img.bpp, &img.line_lenght, &img.endian);
	close (fd);
	return (img);
}

void load_texture(t_data *data)
{
	data->texture.ea_texture = init_img(data, data->texture.ea_path);
	data->texture.no_texture = init_img(data, data->texture.no_path);
	data->texture.so_texture = init_img(data, data->texture.so_path);
	data->texture.we_texture = init_img(data, data->texture.we_path);
}