#include "../includes/cub3D.h"

int render_map_all(t_data *data)
{
	render_map(data);
	mlx_put_image_to_window(data->mlx, data->win, data->current_img.img, 0, 0); 
	return (SUCCESS);
}

int	load_img(t_data *data, t_cardinal_image *img, char *path)
{
	if (path)
	{
	    img->path = path;
	    img->img = mlx_xpm_file_to_image(data->mlx, path, &img->width, &img->height);
	    img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length, &img->endian);
	    return (SUCCESS);
	}
    else
	    return (FAILURE);
}

int load_cardinal_images(t_data *data) //to optimize when retrieving in parsing directly to the
										//cardinal images instead of NO SO EA WE
{
	data->cardinal_image = ft_calloc(4, sizeof(t_cardinal_image));
	load_img(data, &(data->cardinal_image[NORTH]), data->NO);
	load_img(data, &(data->cardinal_image[SOUTH]), data->SO);
	load_img(data, &(data->cardinal_image[EAST]), data->EA);
	load_img(data, &(data->cardinal_image[WEST]), data->WE);
	return (SUCCESS);
}

int init_frame(t_data *data)
{
    get_playermap_start_pos(data);
	data->mlx = mlx_init(); /*loads mlx*/
	if (!data->mlx)
		close_window(data, "Error\nError creating window.", 10);
	data->win = mlx_new_window(data->mlx, INITIAL_XSIZE, INITIAL_YSIZE, GAME_NAME); /*creates a new clean frame*/
	data->current_img.img = mlx_new_image(data->mlx, INITIAL_XSIZE, INITIAL_YSIZE); /*/creates a new clean image to place in the frame*/
	data->current_img.addr = mlx_get_data_addr(data->current_img.img, &(data->current_img.bits_per_pixel),
	&data->current_img.line_length, &data->current_img.endian);
	load_cardinal_images(data);
    return (SUCCESS);
}