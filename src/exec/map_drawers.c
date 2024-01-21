/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_drawers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 20:27:59 by anda-cun          #+#    #+#             */
/*   Updated: 2024/01/21 23:55:32 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->current_img.addr + (y * data->current_img.line_length + x
			* (data->current_img.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_texture_line(int draw_start, int draw_end, t_data *data,
		t_camera *camera, int x)
{
	t_line	line;
	int		direction;
	int		color;

	direction = get_img_direction(data, camera);
	if (direction == ERROR)
		return ;
	line.tex_x = gettex_x(data, camera);
	line.step = 1.0 * data->cardinal_image[direction].height
		/ camera->line_height;
	line.tex_pos = (draw_start - INITIAL_YSIZE / 2 + camera->line_height / 2)
		* line.step;
	while (draw_start++ < draw_end)
	{
		line.tex_y = (int)(line.tex_pos)
			& (int)(data->cardinal_image[direction].height - 1);
		line.tex_pos += line.step;
		line.pos.px = line.tex_x;
		line.pos.py = line.tex_y;
		color = get_img_color(data->cardinal_image[direction], &(line.pos));
		my_mlx_pixel_put(data, x, draw_start, color);
	}
}

static void	draw_floor_and_ceiling(t_data *data, int x, int draw_s, int draw_e)
{
	int	floor;
	int	ceiling;
	int	i;

	floor = create_trgb(0, data->floor->red, data->floor->green,
			data->floor->blue);
	ceiling = create_trgb(0, data->ceiling->red, data->ceiling->green,
			data->ceiling->blue);
	i = 0;
	while (i++ < draw_s)
		my_mlx_pixel_put(data, x, i, ceiling);
	i = draw_e;
	while (i++ < INITIAL_YSIZE)
		my_mlx_pixel_put(data, x, i, floor);
}

int	draw_crosshair(t_data *data)
{
	int	center_x;
	int	center_y;
	int	color;

	if (INITIAL_XSIZE < 4 || INITIAL_YSIZE < 4)
		return (FAILURE);
	center_x = INITIAL_XSIZE / 2 - 4;
	center_y = INITIAL_YSIZE / 2 - 4;
	color = create_trgb(0, 255, 255, 255);
	while (center_x++ < INITIAL_XSIZE / 2 + 3)
		my_mlx_pixel_put(data, center_x, INITIAL_YSIZE / 2, color);
	while (center_y++ < INITIAL_YSIZE / 2 + 3)
		my_mlx_pixel_put(data, INITIAL_XSIZE / 2, center_y, color);
	return (SUCCESS);
}

int	draw_stuff(t_data *data, int x, t_camera *camera)
{
	int	draw_start;
	int	draw_end;

	draw_start = -camera->line_height / 2 + INITIAL_YSIZE / 2;
	draw_end = camera->line_height / 2 + INITIAL_YSIZE / 2;
	if (draw_start < 0)
		draw_start = 0;
	if (draw_end >= INITIAL_YSIZE)
		draw_end = INITIAL_YSIZE - 1;
	if (camera->side == 0)
		camera->wall_x = data->player.py + camera->perp_wall_dist
			* camera->ray_dir_y;
	else
		camera->wall_x = data->player.px + camera->perp_wall_dist
			* camera->ray_dir_x;
	camera->wall_x -= floor((camera->wall_x));
	draw_floor_and_ceiling(data, x, draw_start, draw_end);
	draw_texture_line(draw_start, draw_end, data, camera, x);
	return (SUCCESS);
}
