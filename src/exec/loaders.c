/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loaders.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 20:27:58 by anda-cun          #+#    #+#             */
/*   Updated: 2024/01/23 18:29:22 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	render_map_all(t_data *data)
{
	render_map(data);
	draw_crosshair(data);
	mlx_put_image_to_window(data->mlx, data->win, data->current_img.img, 0, 0);
	return (SUCCESS);
}

int	load_img(t_data *data, t_cardinal_image *img, char *path)
{
	if (path)
	{
		img->path = path;
		img->img = mlx_xpm_file_to_image(data->mlx, path, &img->width,
				&img->height);
		img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
				&img->line_length, &img->endian);
		return (SUCCESS);
	}
	else
		return (FAILURE);
}

int	load_cardinal_images(t_data *data)
{
	load_img(data, &(data->cardinal_image[NORTH]),
		data->cardinal_image[NORTH].path);
	load_img(data, &(data->cardinal_image[SOUTH]),
		data->cardinal_image[SOUTH].path);
	load_img(data, &(data->cardinal_image[EAST]),
		data->cardinal_image[EAST].path);
	load_img(data, &(data->cardinal_image[WEST]),
		data->cardinal_image[WEST].path);
	return (SUCCESS);
}

int	init_frame(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		close_window(data, "Error\nError creating window.", 10);
	data->win = mlx_new_window(data->mlx, INITIAL_XSIZE, INITIAL_YSIZE,
			GAME_NAME);
	data->current_img.img = mlx_new_image(data->mlx, INITIAL_XSIZE,
			INITIAL_YSIZE);
	data->current_img.addr = mlx_get_data_addr(data->current_img.img,
			&(data->current_img.bits_per_pixel), &data->current_img.line_length,
			&data->current_img.endian);
	load_cardinal_images(data);
	return (SUCCESS);
}
