#include "include/cub3d.h"

void	parsing(char *file_name, t_data *data)
{
	validate_file(file_name, data);
	file_to_tab(file_name, data);
	split_file(data);
	// load_texture(data);
	parse_map(data);
	parse_color(data->texture.c_color, data);
	parse_color(data->texture.f_color, data);
	
	// TODO gerer free en cas d'erreur
}

void	cub3d(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		error_msg("Error:\nmlx fail\n", 0, data);
	data->win_ptr = mlx_new_window(data->mlx_ptr, 1000, 1000, "Cub3D");
	if (!data->win_ptr)
	{
		free(data->mlx_ptr);
		error_msg("Error:\nwin fail\n", 0, data);
	}
	mlx_hook(data->win_ptr, 33, 1L << 17, &quit_game, data);
	mlx_hook(data->win_ptr, KeyPress, KeyPressMask, &handle_keypress, data);
	mlx_loop(data->mlx_ptr);
}

int main(int ac, char **argv) 
{
	t_data *data;

	if (ac != 2)
		return (0);
	data = malloc(sizeof(t_data));
	if (!data)
		return (0);
	init_struct(data);
	parsing(argv[1], data);
	// cub3d(data);
	// 	printf("%s", data->texture.c_color);
	// 	printf("%s", data->texture.f_color);
	// 	printf("%s", data->texture.no_path);
	// 	printf("%s", data->texture.so_path);
	// 	printf("%s", data->texture.ea_path);
	// 	printf("%s", data->texture.we_path);
	// for (int i = 0; data->map.map_file[i]; i++) {
	// 	printf("%s\n", data->map.map_file[i]);
	// }
}