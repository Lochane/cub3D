/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 18:23:58 by lsouquie          #+#    #+#             */
/*   Updated: 2024/03/22 18:23:58 by lsouquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	int		allow;
	int		print;
}			t_img;

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
	char	*ref[7];
	int		texture_count[7];
	int		count;

}		t_texture;

typedef struct s_map
{
	double	angle;
	char	**file;
	int		height;
	int		width;
	double	spawn_x;
	double	spawn_y;
	char	spawn_side;
	int		square_size;
	int		ceiling_color;
	int		floor_color;
	int		spawn_count;
}	t_map;

typedef struct s_player
{
	double		x;
	double		y;
	double		fov;
	double		angle;
	float		move_speed;
}	t_player;

typedef struct s_ray
{
	double	*inter_points_x;
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
	int		x;
	int		y;
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
	t_player	player;
}				t_data;

#endif