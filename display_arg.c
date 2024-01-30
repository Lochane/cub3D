#include "include/cub3d.h"

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

int		display_texture(t_data *data) // TODO opti / norme
{
	int i;

	i = 0;
	while(data->cub_file[i])
	{
		 if (ft_strncmp("NO", data->cub_file[i], 2) == 0)
		{
			data->texture.no_path = ft_strdup(data->cub_file[i]);
			if(!data->texture.no_path)
				error_msg("Error\n", 0, data);
			data->texture.no_path = ft_strtrim(data->texture.no_path, "NO");
			data->texture.no_path = ft_strtrim(data->texture.no_path, " ");
			data->texture.count += 1;
		}
		else if (ft_strncmp("SO", data->cub_file[i], 2) == 0)
		{

			data->texture.so_path = ft_strdup(data->cub_file[i]);
			if(!data->texture.so_path)
				error_msg("Error\n", 0, data);
			data->texture.so_path = ft_strtrim(data->texture.so_path, "SO");
			data->texture.so_path = ft_strtrim(data->texture.so_path, " ");
			data->texture.count += 1;
		}
		else if (ft_strncmp("WE", data->cub_file[i], 2) == 0)
		{

			data->texture.we_path = ft_strdup(data->cub_file[i]);
			if(!data->texture.we_path)
				error_msg("Error\n", 0, data);
			data->texture.we_path = ft_strtrim(data->texture.we_path, "WE");
			data->texture.we_path = ft_strtrim(data->texture.we_path, " ");
			data->texture.count += 1;
		}
		else if (ft_strncmp("EA", data->cub_file[i], 2) == 0)
		{
			data->texture.ea_path = ft_strdup(data->cub_file[i]);
			if(!data->texture.ea_path)
				error_msg("Error\n", 0, data);
			data->texture.ea_path = ft_strtrim(data->texture.ea_path, "EA");
			data->texture.ea_path = ft_strtrim(data->texture.ea_path, " ");
			data->texture.count += 1;
		}
		else if (ft_strncmp("C", data->cub_file[i], 1) == 0)
		{
			data->texture.c_color = ft_strdup(data->cub_file[i]);
			if(!data->texture.c_color)
				error_msg("Error\n", 0, data);
			data->texture.c_color = ft_strtrim(data->texture.c_color, "C");
			data->texture.c_color = ft_strtrim(data->texture.c_color, " ");
			data->texture.count += 1;
		}
		else if (ft_strncmp("F", data->cub_file[i], 1) == 0)
		{
			data->texture.f_color = ft_strdup(data->cub_file[i]);
			if(!data->texture.f_color)
				error_msg("Error\n", 0, data);
			data->texture.f_color = ft_strtrim(data->texture.f_color, "F");
			data->texture.f_color = ft_strtrim(data->texture.f_color, " ");
			data->texture.count += 1;
			
		}
		if	(data->texture.count == 6)
			return (i + 1);
		i++;
	}
	return (error_msg("Error:\nWrong texture\n", 0, data), 0);
}

void	split_file(t_data *data)
{
	int i;
	int j;

	i = display_texture(data);
	j = 0;
	while (!ft_strchr(data->cub_file[i], '1'))
		i++;
	data->map.map_height = found_size(data->cub_file, i);
	data->map.map_file = malloc(sizeof(char *) * (data->map.map_height + 1));
	while(data->cub_file[i])
	{
		data->map.map_file[j] = ft_strdup(data->cub_file[i]);
		data->map.map_file[j] = ft_strtrim(data->map.map_file[j], "\n");
		i++;
		j++;
	}
	data->map.map_file[j] = 0;
	free_tab(data->cub_file, data->file_weidht, data, 0);
}

void	validate_file(char *file_name, t_data *data)
{
	int fd;

	if (ft_strncmp(".cub", &file_name[ft_strlen(file_name) -4], ft_strlen(file_name)))
		error_msg("Error:\nfile is not .cub\n", 0, data);
	fd = open(file_name, __O_DIRECTORY);
	if (fd > 0)
		error_msg("Error:\nfd superieur a 0\n", 2, data);
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		error_msg("Error:\nfd inferieur a 0\n", 2, data);
	close (fd);
}

void	file_to_tab(char *mapfile, t_data *data)
{
	int		fd;
	int		i;
	char	*line;

	i = 0;
	fd = open(mapfile, O_RDONLY);
	data->file_weidht = count_line(mapfile, data);
	data->cub_file = malloc(sizeof(char *) * (data->file_weidht + 1));
	if (!data->cub_file)
		return ;
	line = get_next_line(fd);
	if (!line)
		return ;
	while (line)
	{
		data->cub_file[i] = ft_strdup(line);
		free(line);
		line = get_next_line(fd);
		i++;
	}
	data->cub_file[i] = 0;
}