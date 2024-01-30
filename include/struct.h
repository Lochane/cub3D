#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_img
{
	void	*img;
	int		*addr;
	int		bpp;
	int		linelenght;
	int		width;
	int		height;
	int		endian;
	char	*path;
}			t_img;

typedef struct s_sprite
{

}			t_sprite;

typedef struct s_texture
{
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
	char	*f_color;
	char	*c_color;
	t_img	no_texture;
	t_img	so_texture;
	t_img	ea_texture;
	t_img	we_texture;
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
	t_texture	texture;
	t_sprite	sprites;
}				t_data;

#endif