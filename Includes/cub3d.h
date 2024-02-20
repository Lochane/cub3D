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

# define	SCREEN_WIDTH 2560
# define	SCREEN_HEIGHT 1440
#define		ZOOM	1
# define	TILE_SIZE 1 //comment on determine la taille de la tile?
# define	RED 0xFF0000
# define 	GREEN 0x00FF00
# define	PINK 0xC3139E
# define	CYAN 0x00FFFF
# define	YELLOW 0xE8CD22
# define	WHITE 0xFFFFFF
# define	BLACK 0x000000
# define	PURPLE 0x5A0183
//FOV
//roation speed
//player speed

/* PARSING */

void parse_color(char *color, t_data *data);
void parse_map(t_data *data);
void load_texture(t_data *data);


/* DISPLAY_ARG */

void	is_file_valid(char *file_name, t_data *data);
void	file_to_tab(char *mapfile, t_data *data);
void	split_file(t_data *data);
int		parse_texture(t_data *data);


/* EVENTS */

int	handle_keypress(int keysym, t_data *data);
int	quit_game(t_data *data);

/* UTILS */

void 	init_struct(t_data *data);
int		count_line(char *file_name, t_data *data);
int		copy_tab(char **dest, char **src, t_data *data);
int		is_char_valid(char c);
int		found_spawn(char **tab, t_data *data);
int		tab_size(char **tab);

void	error_msg(char *msg, int tofree, t_data *data);
void	free_texture_path(char *msg, int tofree, t_data *data);
void	*free_tab(char **res, size_t i, t_data *data, int allowfree);
void	print_error_and_free(char *error, t_data *data);

void	print_map_info(t_data *data);
void	ft_putstr_fd(char *str, int fd);
int		is_digit(char **tab);
void	parse_color(char *color, t_data *data);
int		count_width(t_data *data);

//EXEC

void	init_window_and_image(t_data *data);
void	init_player(t_data *data);
void	start_game(t_data *data);
void	game_loop(t_data *data);

//MINIMAP


void	mini_map(t_data *data);
void	print_all_rays(t_data *data);

#endif
