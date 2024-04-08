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

int	count_line(char *file_name, t_data *data, int old_fd)
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
		close(old_fd);
		close(fd);
		error_msg("Error\nline is invalide\n", 1, data);
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
