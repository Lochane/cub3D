/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 16:39:03 by malancar          #+#    #+#             */
/*   Updated: 2024/02/12 17:25:10 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Minilibx/mlx.h"

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


int	main()
{
	t_img	img;
	
	void	*mlx;
	void	*win;
	
	int	win_height;
	int	win_width;
	int	img_height;
	int	img_width;
	
	//double		line;
	
	double	x;
	double	y;
	double	x_min;
	double	x_max;
	double	y_max;
	double	y_min;

	double	a;
	double	b;
	
	int		color_pixel;
	
	win_height= 1000;
	win_width = 1000;
	
	color_pixel = 0xFF0000;
	y_min = -5;
	x_min = -5;
	y_max = 5;
	x_max = 5;
	
	a = 2;
	b = 0;
	
	mlx = mlx_init();
	win = mlx_new_window(mlx, win_width,win_height, "TEST");
	img.img = mlx_new_image(mlx, win_width,win_height);
	img.addr = (int *)mlx_get_data_addr(img.img, &img.bpp, &img.line_lenght, &img.endian);
	
	//EQUATION DROITE : y = ax + b => (y - ax + b) /if y entre 0 et 0_1 print pixel
	
	img_height = 0;
	while (img_height < win_height)
	{
		img_width = 0;
		while (img_width < win_width)
		{
			x = x_min + ((x_max- x_min) / win_width) * img_width;
			y = y_max - ((y_max - y_min) /win_height) * img_height;
			if (y - (a * x + b) >= 0 && y - (a * x + b) <= 0.1)
			{
				img.addr[img_height * win_width + img_width] = color_pixel;
			}
			img_width++;
		}
		img_height++;
	}
	mlx_put_image_to_window(mlx, win, img.img, 0, 0);
	mlx_loop(mlx);
	mlx_destroy_window(mlx, win);
}