/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 20:33:45 by lsouquie          #+#    #+#             */
/*   Updated: 2024/03/20 16:38:35 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

int	is_char_valid(char c)
{	
	if (c != '1' && c != '0' && c != ' ' && c != 'P' && c != 'S' && c != 'W'\
		&& c != 'E' && c != '2' && c != 'N')
		return (0);
	return (1);
}

void	check_spawn(int c, char **tab, t_data *data)
{
	if (c != 1)
	{
		free_tab(tab, data->map.height, data, 0);
		free_texture_path("Error:\nWrong spawn\n", 1, data);
	}
}

int	found_spawn(char **tab, t_data *data)
{
	int	i;
	int	j;
	int	c;

	i = 0;
	j = 0;
	c = 0;
	while (i < data->map.height)
	{
		j = 0;
		while (tab[i][j] && (tab[i][j] != 'N' && tab[i][j] != 'S' && \
			tab[i][j] != 'W' && tab[i][j] != 'E'))
			j++;
		if (tab[i][j] == 'N' || tab[i][j] == 'S' || tab[i][j] == 'W' \
			|| tab[i][j] == 'E')
		{
			data->map.spawn_x = j;
			data->map.spawn_y = i;
			data->map.spawn_side = tab[i][j];
			c += 1;
		}
		i++;
	}
	check_spawn(c, tab, data);
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
