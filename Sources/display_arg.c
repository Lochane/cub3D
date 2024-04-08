/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_arg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 13:29:06 by lsouquie          #+#    #+#             */
/*   Updated: 2024/02/08 13:29:06 by lsouquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

char	*display_texture(t_data *data, const char *set, const char *to_copy)
{
	char	*str;
	char	*tmp;

	tmp = ft_strdup(to_copy);
	if (!tmp)
		return (NULL);
	tmp = ft_strtrim(tmp, " ");
	if (!tmp)
		return (NULL);
	tmp = ft_strtrim(tmp, set);
	if (!tmp)
		return (NULL);
	tmp = ft_strtrim(tmp, " ");
	if (!tmp)
		return (NULL);
	tmp = ft_strtrim(tmp, "\n");
	if (!tmp)
		return (NULL);
	tmp = ft_strtrim(tmp, " ");
	if (!tmp)
		return (NULL);
	data->texture.count += 1;
	str = ft_strdup(tmp);
	free(tmp);
	return (str);
}

void	init_color(t_data *data, int i, char **tmp)
{
	if (tmp[0])
	{
		if (ft_strcmp("NO", tmp[0]) == 0)
			data->texture.no_path = display_texture(data, "NO", \
				data->cub_file[i]);
		else if (ft_strcmp("SO", tmp[0]) == 0)
			data->texture.so_path = display_texture(data, "SO", \
				data->cub_file[i]);
		else if (ft_strcmp("WE", tmp[0]) == 0)
			data->texture.we_path = display_texture(data, "WE", \
				data->cub_file[i]);
		else if (ft_strcmp("EA", tmp[0]) == 0)
			data->texture.ea_path = display_texture(data, "EA", \
				data->cub_file[i]);
		else if (ft_strcmp("C", tmp[0]) == 0)
			data->texture.ceiling_color = display_texture(data, "C", \
					data->cub_file[i]);
		else if (ft_strcmp("F", tmp[0]) == 0)
			data->texture.floor_color = display_texture(data, "F", \
				data->cub_file[i]);
	}
}

int	init_texture(t_data *data)
{
	int		i;
	char	**tmp;

	i = 0;
	tmp = NULL;
	count_texture(data);
	while (data->cub_file[i])
	{
		tmp = ft_split(data->cub_file[i], ' ');
		if (!tmp)
		{
			free_tab(tmp, found_size(tmp, 0), data, 0);
			return (free_texture_path("Error:\n Wrong config\n", 1, data), 0);
		}
		check_wrong_char(tmp, data);
		init_color(data, i, tmp);
		if (data->texture.count == 6)
			return (free_tab(tmp, found_size(tmp, 0), data, 0), i + 1);
		free_tab(tmp, found_size(tmp, 0), data, 0);
		i++;
	}
	return (free_texture_path("Error:\n Wrong config\n", 1, data), 0);
}

void	split_file(t_data *data)
{
	int	i;
	int	j;

	i = init_texture(data);
	j = 0;
	while (data->cub_file[i] && !ft_strchr(data->cub_file[i], '1'))
		i++;
	if (!data->cub_file[i])
		free_texture_path("Error:\n Wrong config\n", 1, data);
	check_size(i, data);
	data->map.file = malloc(sizeof(char *) * (data->map.height + 1));
	if (!data->map.file)
		split_free_error(data, 0);
	while (data->cub_file[i])
	{
		data->map.file[j] = ft_strdup(data->cub_file[i]);
		if (!data->map.file[j])
			split_free_error(data, 1);
		data->map.file[j] = ft_strtrim(data->map.file[j], "\n");
		if (!data->map.file[j++])
			split_free_error(data, 1);
		i++;
	}
	data->map.file[j] = 0;
	free_tab(data->cub_file, data->file_weidht, data, 0);
}

void	file_to_tab(char *mapfile, t_data *data)
{
	int		fd;
	int		i;
	char	*line;

	i = 0;
	fd = open(mapfile, O_RDONLY);
	if (fd < 0)
		print_error_and_free("open", data);
	data->file_weidht = count_line(mapfile, data, fd);
	data->cub_file = malloc(sizeof(char *) * (data->file_weidht + 1));
	if (!data->cub_file)
		print_error_and_free("malloc", data);
	line = get_next_line(fd);
	if (!line)
		error_msg("Error:\nmalloc\n", 1, data);
	while (line)
	{
		data->cub_file[i++] = ft_strdup(line);
		free(line);
		if (!data->cub_file)
			error_msg("Error:\nmalloc\n", 1, data);
		line = get_next_line(fd);
	}
	close(fd);
	data->cub_file[i] = 0;
}
