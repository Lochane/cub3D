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
	char	**file;
	int		height;
	int 	width;
	int		spawn_x;
	int		spawn_y;
	char	spawn_side;
	int		square_size;
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
} t_ray;

typedef struct s_moves
{
	float movespeed;
	float rotspeed;
	float posx;
	float posy;
	float planex;
	float planey;
	float dirx;
	float diry;
	float olddirx;
	float oldplanex;
}	t_moves;

typedef struct s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	char		**cub_file;
	int			file_weidht;
	int			win_height;
	int			win_width;
	t_ray		ray;
	t_map		map;
	t_img		img;
	t_moves		moves;
	t_texture	texture;
	t_player	player;
}				t_data;

#endif