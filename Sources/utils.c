/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 15:55:37 by malancar          #+#    #+#             */
/*   Updated: 2024/02/08 15:55:37 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

int	found_size(char **file, int i)
{
	int	line;

	line = 0;
	while (file[i])
	{
		line++;
		i++;
	}
	return (line);
}

int	count_width(t_data *data)
{
	int	i;
	int	len;
	int	len_max;

	len = 0;
	len_max = 0;
	i = 0;
	while (data->map.file[i])
	{
		len = ft_strlen(data->map.file[i]);
		if (len > len_max)
			len_max = len;
		i++;
	}
	return (len_max);
}

int	tab_size(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

int	count_line(char *file_name, t_data *data)
{
	int		fd;
	int		i;
	char	*line;

	i = 0;
	fd = open(file_name, O_RDONLY);
	line = get_next_line(fd);
	if (!line)
	{
		free(line);
		close(fd);
		error_msg("Error: line is invalide\n", 1, data);
	}
	while (line)
	{
		i++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	free(line);
	return (i);
}

int	copy_tab(char **dest, char **src, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->map.height)
	{
		dest[i] = ft_strdup(src[i]);
		if (!dest)
			return (0);
		i++;
	}
	dest[i] = 0;
	return (1);
}

//DEBUG
void	print_map_info(t_data *data)
{
	printf("%s\n", data->texture.ceiling_color);
	printf("%s\n", data->texture.floor_color);
	printf("%s\n", data->texture.no_path);
	printf("%s\n", data->texture.so_path);
	printf("%s\n", data->texture.ea_path);
	printf("%s\n", data->texture.we_path);
	for (int i = 0; data->map.file[i]; i++)
		printf("%s\n", data->map.file[i]);
}

