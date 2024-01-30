#ifndef CUB3D_H
#define CUB3D_H

# include "../libft/libft.h"
# include "struct.h"
# include "../minilibx-linux/mlx.h"
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <sys/time.h>

/* PARSING */

void	validate_file(char *file_name, t_data *data);
void	file_to_tab(char *mapfile, t_data *data);
int		parse_texture(t_data *data);


/* UTILS */

void 	init_struct(t_data *data);
void	error_msg(char *msg, int tofree, t_data *data);
void	*free_tab(char **res, size_t i, t_data *data, int allowfree);
int		count_line(char *file_name, t_data *data);
void	copy_tab(char **dest, char **src, t_data *data);
int		found_spawn(char **tab, t_data *data);


#endif