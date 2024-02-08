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

void	validate_chars(t_data *data, char c)
{	
	if (c != '1' && c != '0' && c != ' ' &&  c != 'P' &&  c != 'S' &&  c != 'W' &&  c != 'E' && c != '2')
		error_msg("Error:\nCharacter invalid\n", 1, data);
}

int	found_spawn(char **tab, t_data *data)
{
	int	i;
	int	j;
	int c;

	i = 0;
	j = 0;
	c = 0; 
	while (i < data->map.map_height)
	{
		j = 0;
		while (tab[i][j] && (tab[i][j] != 'N' && tab[i][j] != 'S' && tab[i][j] != 'W' && tab[i][j] != 'E'))
			j++;
		if (tab[i][j] == 'N' || tab[i][j] == 'S' || tab[i][j] == 'W' || tab[i][j] == 'E')
		{
			data->map.spawn_x = j;
			data->map.spawn_y = i;
			c += 1;
		}
		i++;
	}
	if (c > 1 || c <= 0)
		error_msg("Error:\n Wrong spawn\n", 0, data);
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
	data->texture.count = 0;
	data->file_weidht = 0;
	// data->map.map_file = NULL;
	// data->texture.c_color = NULL;
	// data->texture.f_color = NULL;
	// data->texture.no_path = NULL;
	// data->texture.so_path = NULL;
	// data->texture.we_path = NULL;
	// data->texture.ea_path = NULL;
	// data->texture.texture_file= NULL;

}