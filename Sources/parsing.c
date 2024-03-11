/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 17:13:33 by lsouquie          #+#    #+#             */
/*   Updated: 2024/03/11 19:01:15 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

int	flood_fill(int x, int y, char **file, t_data *data)
{
	if (y < 0 || x < 0 || file[x][y] == ' ' || x > data->map.height \
		|| y > (int)ft_strlen(file[x]) || !file[x][y])
		return (0);
	if (file[x][y] == '1' || file[x][y] == '2')
		return (1);
	if (file[x][y] == '0')
		file[x][y] = '2';
	if (!flood_fill(x +1, y, file, data))
		return (0);
	if (!flood_fill(x - 1, y, file, data))
		return (0);
	if (!flood_fill(x, y + 1, file, data))
		return (0);
	if (!flood_fill(x, y - 1, file, data))
		return (0);
	return (1);
}

void	error_parse_map(t_data *data, char **tmp)
{
	free_tab(tmp, data->map.height, data, 0);
	free_texture_path("1Error: malloc\n", 1, data);
}

void	check_map(t_data *data, char **tmp, int i, int j)
{
	if (!is_char_valid(tmp[i][j]))
		error_parse_map(data, tmp);
	if (tmp[i][j] == '0')
	{
		if (!flood_fill(i, j, tmp, data))
			error_parse_map(data, tmp);
	}
}

void	parse_map(t_data *data)
{
	int		i;
	int		j;
	char	**tmp;

	i = 0;
	j = 0;
	tmp = malloc(sizeof(char **) * (data->map.height + 1));
	if (!tmp)
		free_texture_path("2Error malloc\n", 1, data);
	if (!copy_tab(tmp, data->map.file, data))
		error_parse_map(data, tmp);
	found_spawn(tmp, data);
	while (tmp[i])
	{
		j = 0;
		while (tmp[i][j])
		{
			check_map(data, tmp, i, j);
			j++;
		}
		i++;
	}
	free_tab(tmp, data->map.height, data, 0);
}
