#ifndef CUB3D_H
#define CUB3D_H

# include "../libft/libft.h"
# include "struct.h"
# include "../Minilibx/mlx.h"
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <sys/time.h>


/* PARSING */

void parse_color(char *color, t_data *data);
void parse_map(t_data *data);
void load_texture(t_data *data);


/* DISPLAY_ARG */

void	validate_file(char *file_name, t_data *data);
void	file_to_tab(char *mapfile, t_data *data);
void	split_file(t_data *data);
int		parse_texture(t_data *data);


/* EVENTS */

int	handle_keypress(int keysym, t_data *data);
int	quit_game(t_data *data);

/* UTILS */

void 	init_struct(t_data *data);
void	error_msg(char *msg, int tofree, t_data *data);
void	*free_tab(char **res, size_t i, t_data *data, int allowfree);
int		count_line(char *file_name, t_data *data);
int		copy_tab(char **dest, char **src, t_data *data);
int		validate_chars(char c);
int		found_spawn(char **tab, t_data *data);
int		tab_size(char **tab);
void	ft_free_texture_path(char *msg, int tofree, t_data *data);


#endif