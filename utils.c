#include "include/cub3d.h"

void	error_msg(char *msg, int tofree, t_data *data)
{
	(void)tofree;
	free(data);
	write(2, msg, ft_strlen(msg));
	exit (0);
}

void	*free_tab(char **res, size_t i, t_data *data, int allowfree)
{
	while (i-- > 0)
		free(res[i]);
	free(res);
	if (allowfree == 1)
		free(data);
	return (NULL);
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
		error_msg("Error:\nline is invalide\n", 1, data);
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

void	copy_tab(char **dest, char **src, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->map.map_height)
	{
		dest[i] = ft_strdup(src[i]);
		i++;
	}
}

int	found_spawn(char **tab, t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < data->map.map_height)
	{
		j = 0;
		while (tab[i][j] && tab[i][j] != 'P')
			j++;
		if (tab[i][j] == 'P')
		{
			data->map.spawn_x = j;
			data->map.spawn_y = i;
			break ;
		}
		i++;
	}
	return (0);
}

void init_struct(t_data *data)
{
	// data->mlx_ptr = NULL;
	// data->win_ptr = NULL;
	// data->cub_file = NULL;
	data->map.map_widht = 0;
	data->map.map_height = 0;
	data->map.spawn_y = 0;
	data->map.spawn_x = 0;
	data->map.spawn_side = 0;
	data->cub_file = NULL;
	data->map.map_texture.count = 0;

	// data->map.map_file = NULL;
	// data->map.map_texture.c_color = NULL;
	// data->map.map_texture.f_color = NULL;
	// data->map.map_texture.no_path = NULL;
	// data->map.map_texture.so_path = NULL;
	// data->map.map_texture.we_path = NULL;
	// data->map.map_texture.ea_path = NULL;
	// data->map.map_texture.texture_file= NULL;

}