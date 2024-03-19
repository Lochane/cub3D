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
	int		allow;
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
	char	*floor_color;
	char	*ceiling_color;
	t_img	no_texture;
	t_img	so_texture;
	t_img	ea_texture;
	t_img	we_texture;
	double	pixel_y;
	double	pixel_x;
	int		count;

} t_texture;

typedef struct s_map
{
	char	**file;
	int		height;
	int 	width;
	double	spawn_x;
	double	spawn_y;
	char	spawn_side;
	int		square_size;
	int		ceiling_color[3];
	int		floor_color[3];
} t_map;

typedef	struct s_player
{
	double		x;
	double		y;
	double		center_x;
	double		center_y;
	double	fov;//field of view in radians
	double	angle;
	float	move_speed;
	double	dirx;
	double	diry;
	//int		rotation_flag;
	//int		left_rotation;
	//int		right_rotation;
} t_player;

typedef	struct s_ray
{
	double	*inter_points_x;
	double	*inter_points_y;
	double	*angles;
	double	h_inter_x;
	double	h_inter_y;
	double	v_inter_x;
	double	v_inter_y;
	double	inter_x;
	double	inter_y;
	int		is_horizontal;
	double	distance;
	double	angle;
	double	a;
	double	b;
	int		x;
	int		y;
	int		center;
	int		start_height;
	int		start_width;
	int		end_height;
	int		end_width;
	int		ray_index;
	double	dirx;
	double	diry;
}	t_ray;

typedef struct s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	char		**cub_file;
	int			file_weidht;
	int			win_height;
	int			win_width;
	int			key_press;
	t_ray		ray;
	t_map		map;
	t_img		img;
	t_texture	texture;
	t_sprite	sprites;
	t_player	player;
}				t_data;

#endif