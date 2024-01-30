#include "include/cub3d.h"

void	parsing_map(char *file_name, t_data *data)
{
	validate_file(file_name, data);
	file_to_tab(file_name, data);
	parse_texture(data);
	// split_file(data);
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
	parsing_map(argv[1], data);
	// for (int i = 0; data->cub_file[i]; i++) {
		printf("%s", data->map.map_texture.c_color);
	// }
}