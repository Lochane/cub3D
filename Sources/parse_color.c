/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:57:27 by malancar          #+#    #+#             */
/*   Updated: 2024/03/20 17:53:54 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

int		rgb_to_int(int red, int green, int blue)
{
	return((red << 16) | (green << 8) | blue);
}


int	count_nbr(char *str)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == ',')
			count++;
		i++;
	}
	return (count);
}

int	is_color_rgb(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{	
		if ((ft_atoi(tab[i]) < 0 || ft_atoi(tab[i]) > 255))
			break ;
		i++;
	}
	return (i);
}

int	is_digit(char **tab)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (tab[i])
	{
		j = 0;
		while (tab[i][j])
		{
			if (tab[i][j] < '0' || tab[i][j] > '9')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	parse_color(char *color, t_data *data)
{
	int		i;
	char	**tab;

	i = count_nbr(color);
	if (i != 2)
		free_texture_path("Error:1 Color not valid, expected RGB color,\
digit between 000,000,000 and : 255,255,255\n", 1, data);
	tab = ft_split(color, ',');
	if (!tab)
		free_texture_path("Error: 2Color not valid, expected RGB color, \
digit between 000,000,000 and : 255,255,255\n", 1, data);
	i = 0;
	if (!is_digit(tab))
		free_texture_path("Error:3Color not valid, expected RGB color, \
digit between 000,000,000 and : 255,255,255\n", 1, data);
	i = is_color_rgb(tab);
	if (i != 3)
	{
		free_tab(tab, tab_size(tab), data, 0);
		free_texture_path("Error:4 Color not valid, expected RGB color, \
digit between 000,000,000 and : 255,255,255\n", 1, data);
	}
	//free_tab(tab, i, data, 0);
	return(rgb_to_int(ft_atoi(tab[0]), ft_atoi(tab[1]), ft_atoi(tab[2])));
}
