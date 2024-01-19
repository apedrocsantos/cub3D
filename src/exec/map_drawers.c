#include "../includes/cub3D.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->current_img.addr + (y * data->current_img.line_length + 
		x * (data->current_img.bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	draw_textureLine(int drawStart, int drawEnd, t_data *data, t_camera *camera, int x)
{
	t_line line;
	int direction = getImgDirection(data, camera);
	if (direction == ERROR)
		return ;
	line.tex_x = gettex_x(data, camera);
    line.step = 1.0 * data->cardinal_image[direction].height / camera->line_height;
    line.tex_pos = (drawStart - INITIAL_YSIZE / 2 + camera->line_height / 2) * line.step;
    while (drawStart++ < drawEnd)
    {
        line.tex_y = (int)(line.tex_pos) & (data->cardinal_image[direction].height - 1);
        line.tex_pos += line.step;
		line.pos.px = line.tex_x;
		line.pos.py = line.tex_y;
        int color = get_img_color(data->cardinal_image[direction], &(line.pos));
        // if(camera->side == 1)
		// 	color = (color >> 1) & 8355711;
        my_mlx_pixel_put(data, x, drawStart, color);
    }
}

static void drawFloorAndCeiling(t_data *data, int x, int drawStart, int drawEnd)
{
	int F;
	int C;
	int i;

	F = create_trgb(0, data->floor->red, data->floor->green, data->floor->blue);
	C = create_trgb(0, data->ceiling->red, data->ceiling->green, data->ceiling->blue);
	i = 0;
	while (i++ < drawStart)
		my_mlx_pixel_put(data, x, i, C);
	i = drawEnd;
	while (i++ < INITIAL_YSIZE)
		my_mlx_pixel_put(data, x, i, F);
}

int draw_crosshair(t_data *data)
{
	if (INITIAL_XSIZE < 4 || INITIAL_YSIZE < 4)
		return (FAILURE);
	int centerX = INITIAL_XSIZE/2 - 4;
	int centerY = INITIAL_YSIZE/2 - 4;
	int color = create_trgb(0, 255, 255, 255);
	while (centerX++ < INITIAL_XSIZE/2 + 3)
		my_mlx_pixel_put(data, centerX, INITIAL_YSIZE/2, color);
	while (centerY++ < INITIAL_YSIZE/2 + 3)
		my_mlx_pixel_put(data, INITIAL_XSIZE/2, centerY, color);
	return (SUCCESS);
}

int draw_stuff(t_data *data, int x, t_camera *camera)
{
	int drawStart;
	int drawEnd;

	drawStart = -camera->line_height / 2 + INITIAL_YSIZE / 2;
	drawEnd = camera->line_height / 2 + INITIAL_YSIZE / 2;
    if (drawStart < 0)
        drawStart = 0;
    if (drawEnd >= INITIAL_YSIZE)
        drawEnd = INITIAL_YSIZE - 1;
    if (camera->side == 0)
		camera->wall_x = data->player.py + camera->perp_wall_dist * camera->ray_dir_y;
    else
		camera->wall_x = data->player.px + camera->perp_wall_dist * camera->ray_dir_x;
    camera->wall_x -= floor((camera->wall_x));
	drawFloorAndCeiling(data,x, drawStart, drawEnd);
	draw_textureLine(drawStart, drawEnd, data, camera, x);
	return (SUCCESS);
}