/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 17:07:10 by lsouquie          #+#    #+#             */
/*   Updated: 2024/03/21 17:07:10 by lsouquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "struct.h"
# include "../Minilibx/mlx.h"
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <sys/time.h>
# include <math.h>
# include <limits.h>

# define SCREEN_WIDTH 2560
# define SCREEN_HEIGHT 1440
# define ZOOM	0.25
# define FOV	60
# define TILE_SIZE 1
# define RED 0xFF0000
# define GREEN 0x00FF00
# define PINK 0xC3139E
# define CYAN 0x00FFFF
# define YELLOW 0xE8CD22
# define WHITE 0xFFFFFF
# define BLACK 0x000000
# define PURPLE 0x5A0183
# define LEFT_KEY 65361
# define RIGHT_KEY 65363
# define BLUE 0x0000FF

/* PARSING */

int		parse_color(char *color, t_data *data);
void	parse_map(t_data *data);
void	load_texture(t_data *data);

/* DISPLAY_ARG */

void	is_file_valid(char *file_name, t_data *data);
void	file_to_tab(char *mapfile, t_data *data);
void	split_file(t_data *data);
int		parse_texture(t_data *data);
void	count_texture(t_data *data);
void	check_wrong_char(char **tmp, t_data *data);
void	check_size(int i, t_data *data);

/* EVENTS */

int		keybinding(int keysim, t_data *data);
int		handle_keypress(int keysym, t_data *data);
int		handle_key_release(int key_sym, t_data *data);
int		quit_game(t_data *data);

/* UTILS */

void	init_struct(t_data *data);
void	init_moves(t_data *data);
int		count_line(char *file_name, t_data *data, int old_fd);
int		copy_tab(char **dest, char **src, t_data *data);
int		is_char_valid(char c);
int		found_spawn(char **tab, t_data *data);
int		tab_size(char **tab);
int		found_size(char **file, int i);

void	error_msg(char *msg, int tofree, t_data *data);
void	free_texture_path(char *msg, int tofree, t_data *data);
void	*free_tab(char **res, size_t i, t_data *data, int allowfree);
void	print_error_and_free(char *error, t_data *data);
void	split_free_error(t_data *data, int to_free);

void	ft_putstr_fd(char *str, int fd);
int		is_digit(char **tab);
void	error_parse_map(t_data *data, char **tmp);

int		count_width(t_data *data);

//EXEC

void	init_game(t_data *data);
void	init_window_and_image(t_data *data);
void	init_player(t_data *data);
void	start_game(t_data *data);
int		game(t_data *data);
int		is_wall(t_data *data, double intersection_x, double intersection_y, \
					double angle);

int		render_texture(t_data *data, int height, int beg_wall, int end_wall);

//MINIMAP

void	init_square_size(t_data *data);
void	mini_map(t_data *data);
void	print_all_rays(t_data *data);
void	display_ray_mm(t_data *data);
void	mini_map_rays(t_data *data);

/* GAMEPLAY */
void	raycasting(t_data *data);
void	render_wall(t_data *data, int width);
double	find_horizontal_intersection(t_data *data, double angle);
double	find_vertical_intersection(t_data *data, double angle);

#endif
