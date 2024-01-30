#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_texture
{
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
	char	*f_color;
	char	*c_color;
	int		count;

} t_texture;

typedef struct s_map
{
	char **map_file;
	int		map_height;
	int 	map_widht;
	int		spawn_x;
	int		spawn_y;
	char	spawn_side;
	t_texture	map_texture;	
} t_map;

typedef struct s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	char		**cub_file;
	int			file_weidht;
	t_map		map;
}				t_data;

#endif