#include "include/cub3d.h"

int		parse_texture(t_data *data) // TODO opti / norme
{
	int i;

	i = 0;
	while(data->cub_file[i])
	{
		// ft_printf("%s", data->cub_file[i]);
		if (ft_strncmp("NO", data->cub_file[i], 3))
		{
			// printf("lol");

		printf("1 -%s", data->cub_file[i]);
			data->map.map_texture.no_path = ft_strdup(data->cub_file[i++]);
			if(!data->map.map_texture.no_path)
				error_msg("Error\n", 0, data);
			data->map.map_texture.count += 1;
			
		}
		if (ft_strncmp("SO", data->cub_file[i], 3))
		{
		printf("2 -%s", data->cub_file[i]);
			data->map.map_texture.so_path = ft_strdup(data->cub_file[i++]);
			if(!data->map.map_texture.so_path)
				error_msg("Error\n", 0, data);
			data->map.map_texture.count += 1;

		}
		if (ft_strncmp("WE", data->cub_file[i], 3))
		{
		printf("3 -%s", data->cub_file[i]);
			data->map.map_texture.we_path = ft_strdup(data->cub_file[i++]);
			if(!data->map.map_texture.we_path)
				error_msg("Error\n", 0, data);
			data->map.map_texture.count += 1;

		}
		if (ft_strncmp("EA", data->cub_file[i], 3))
		{
		printf("4 -%s", data->cub_file[i]);
			data->map.map_texture.ea_path = ft_strdup(data->cub_file[i++]);
			if(!data->map.map_texture.ea_path)
				error_msg("Error\n", 0, data);
			data->map.map_texture.count += 1;
		}
		if (ft_strncmp("C", data->cub_file[i], 3))
		{
		printf("5 -%s", data->cub_file[i]);
			data->map.map_texture.c_color = ft_strdup(data->cub_file[i++]);
			if(!data->map.map_texture.c_color)
				error_msg("Error\n", 0, data);
			data->map.map_texture.count += 1;
		}
		if (ft_strncmp("F", data->cub_file[i], 3))
		{
		printf("6 -%s", data->cub_file[i]);
			data->map.map_texture.f_color = ft_strdup(data->cub_file[i++]);
			if(!data->map.map_texture.f_color)
				error_msg("Error\n", 0, data);
			data->map.map_texture.count += 1;
			
		}
		if	(data->map.map_texture.count == 6)
			return (i);
		i++;
	}
	return (0);
}

// void	split_file(t_data *data)
// {
// 	int i;

// 	i = 0;
// 	// while (data->cub_file[i])
// 	// {

// 	// }
// }

void	validate_file(char *file_name, t_data *data)
{
	int fd;

	if (ft_strncmp(".cub", &file_name[ft_strlen(file_name) -4], ft_strlen(file_name)))
		error_msg("Error:\nfile is not .cub\n", 0, data);
	fd = open(file_name, __O_DIRECTORY);
	if (fd > 0)
		error_msg("Error:\nfd superieur a 0\n", 2, data);
	fd = open(file_name, O_RDONLY);
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
}