/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 20:33:45 by lsouquie          #+#    #+#             */
/*   Updated: 2024/04/08 17:43:31 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

int	is_char_valid(char c)
{	
	if (c != '1' && c != '0' && c != ' ' && c != 'P' && c != 'S' && c != 'W'\
		&& c != 'E' && c != 'N')
		return (0);
	return (1);
}

void	check_spawn(char **tab, t_data *data)
{
	if (data->map.spawn_count != 1)
	{
		free_tab(tab, data->map.height, data, 0);
		free_texture_path("Error\n1Wrong map\n", 2, data);
	}
}

int	found_spawn(char **tab, t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < data->map.height)
	{
		j = 0;
		while (tab[i][j])
		{
			j++;
			if (tab[i][j] == 'N' || tab[i][j] == 'S' || tab[i][j] == 'W' \
				|| tab[i][j] == 'E')
			{
				data->map.spawn_x = j;
				data->map.spawn_y = i;
				data->map.spawn_side = tab[i][j];
				data->map.spawn_count++;
			}
		}
		i++;
	}
	check_spawn(tab, data);
	return (0);
}

void	ft_putstr_fd(char *str, int fd)
{
	int	len;

	if (str == NULL)
		return ;
	len = ft_strlen(str);
	if (write(fd, str, len) == -1)
		perror("write");
}

void	error_parse_map(t_data *data, char **tmp)
{
	free_tab(tmp, data->map.height, data, 0);
	free_texture_path("Error\n2Wrong map\n", 2, data);
	exit(0);
}
