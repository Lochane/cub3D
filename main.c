#include "include/cub3d.h"

void	parsing(char *file_name, t_data *data)
{
	validate_file(file_name, data);
	file_to_tab(file_name, data);
	split_file(data);
	parse_map(data);
	parse_color(data->texture.c_color, data);
	parse_color(data->texture.f_color, data);
	// parse_texture(data);
	
	// TODO gerer free en cas d'erreur
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
		printf("%s", data->texture.c_color);
		printf("%s", data->texture.f_color);
		printf("%s", data->texture.no_path);
		printf("%s", data->texture.so_path);
		printf("%s", data->texture.ea_path);
		printf("%s", data->texture.we_path);
	for (int i = 0; data->map.map_file[i]; i++) {
		printf("%s\n", data->map.map_file[i]);
	}
}