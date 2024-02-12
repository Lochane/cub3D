#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_img
{
	void	*img;
	int		*addr;
	int		bpp;
	int		line_lenght;
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
} t_map;

typedef	struct s_player
{
	int		x;
	int		y;
	float	fov;//field of view in radians
	double	angle;
	//int		rotation_flag;
	//int		left_rotation;
	//int		right_rotation;
} t_player;

typedef	struct s_ray
{
	double	ray_angle;
	double	distance;
	//int		flag;//c'est quoi flag?
};


typedef struct s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	char		**cub_file;
	int			file_weidht;
	int			win_height;
	int			win_width;
	t_map		map;
	t_img		img;
	t_texture	texture;
	t_sprite	sprites;
	t_player	player;
}				t_data;

#endif