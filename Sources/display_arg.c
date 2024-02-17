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

int found_size(char **file, int i)
{
	int line;

	line = 0;
	while(file[i])
	{
		line++;
		i++;
	}
	return (line);
}

char *display_texture(t_data *data, const char *set, const char *to_copy)
{
	char *str;

	str = ft_strdup(to_copy);
	if(!str)
		return NULL;
	str = ft_strtrim(str, set);
	if(!str)
		return NULL;
	str = ft_strtrim(str, " ");
	if(!str)
		return NULL;
	str = ft_strtrim(str, "\n");
	if(!str)
		return NULL;
	data->texture.count += 1;
	return (str);
}

int		init_texture(t_data *data) // TODO opti / norme
{
	int i;

	i = 0;
	while(data->cub_file[i])
	{
		 if (ft_strncmp("NO", data->cub_file[i], 2) == 0)
			data->texture.no_path = display_texture(data, "NO", data->cub_file[i]);
		else if (ft_strncmp("SO", data->cub_file[i], 2) == 0)
			data->texture.so_path = display_texture(data, "SO", data->cub_file[i]);
		else if (ft_strncmp("WE", data->cub_file[i], 2) == 0)
			data->texture.we_path = display_texture(data, "WE", data->cub_file[i]);
		else if (ft_strncmp("EA", data->cub_file[i], 2) == 0)
			data->texture.ea_path = display_texture(data, "EA", data->cub_file[i]);
		else if (ft_strncmp("C", data->cub_file[i], 1) == 0)
			data->texture.c_color = display_texture(data, "C", data->cub_file[i]);
		else if (ft_strncmp("F", data->cub_file[i], 1) == 0)
			data->texture.f_color = display_texture(data, "F", data->cub_file[i]);
		if	(data->texture.count == 6)
			return (i + 1);
		i++;
	}
	return (free_texture_path("Error:\nWrong texture\n", 1, data), 0);
}

void	split_file(t_data *data)
{
	int i;
	int j;

	i = init_texture(data);
	j = 0;
	while (!ft_strchr(data->cub_file[i], '1'))
		i++;
	data->map.height = found_size(data->cub_file, i);
	data->map.file = malloc(sizeof(char *) * (data->map.height + 1));
	if(!data->map.file)
	{
		free_texture_path(NULL, 4, data);
		error_msg("Error:\n Erreur Malloc", 1, data);
	}
	while(data->cub_file[i])
	{
		data->map.file[j] = ft_strdup(data->cub_file[i]);
		if (!data->map.file[j])
		{
			free_texture_path(NULL, 4, data);
			free_tab(data->map.file, data->map.height, data, 0);
			error_msg("Error:\n Erreur Malloc", 1, data);
		}
		data->map.file[j] = ft_strtrim(data->map.file[j], "\n");
		if (!data->map.file[j])
		{
			free_texture_path(NULL, 4, data);
			free_tab(data->map.file, data->map.height, data, 0);
			error_msg("Error:\n Erreur Malloc", 1, data);
		}
		i++;
		j++;
	}
	data->map.file[j] = 0;
	free_tab(data->cub_file, data->file_weidht, data, 0);
}

void	is_file_valid(char *file_name, t_data *data)
{
	int fd;

	if (ft_strncmp(".cub", &file_name[ft_strlen(file_name) -4], ft_strlen(file_name)))
		error_msg("Error: expected [file.cub]\n", 0, data);
	fd = open(file_name, __O_DIRECTORY);
	if (fd > 0)
		print_error_and_free("open", data);
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		print_error_and_free("open", data);
	close (fd);
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
	data->file_weidht = count_line(mapfile, data);
	data->cub_file = malloc(sizeof(char *) * (data->file_weidht + 1));
	if (!data->cub_file)
		print_error_and_free("malloc", data);
	line = get_next_line(fd);
	if (!line)
		print_error_and_free("malloc", data);
	while (line)
	{
		data->cub_file[i] = ft_strdup(line);
		free(line);
		if (!data->cub_file)
			print_error_and_free("malloc", data);
		line = get_next_line(fd);
		i++;
	}
	data->cub_file[i] = 0;
}
