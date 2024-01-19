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
	line.texX = getTexX(data, camera);
    line.step = 1.0 * data->cardinal_image[direction].height / camera->lineHeight;
    line.texPos = (drawStart - INITIAL_YSIZE / 2 + camera->lineHeight / 2) * line.step;
    while (drawStart++ < drawEnd)
    {
        line.texY = (int)(line.texPos) & (data->cardinal_image[direction].height - 1);
        line.texPos += line.step;
		line.pos.px = line.texX;
		line.pos.py = line.texY;
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

	F = create_trgb(0, data->F->R, data->F->G, data->F->B);
	C = create_trgb(0, data->C->R, data->C->G, data->C->B);
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

	drawStart = -camera->lineHeight / 2 + INITIAL_YSIZE / 2;
	drawEnd = camera->lineHeight / 2 + INITIAL_YSIZE / 2;
    if (drawStart < 0)
        drawStart = 0;
    if (drawEnd >= INITIAL_YSIZE)
        drawEnd = INITIAL_YSIZE - 1;
    if (camera->side == 0)
		camera->wallX = data->player.py + camera->perpWallDist * camera->rayDirY;
    else
		camera->wallX = data->player.px + camera->perpWallDist * camera->rayDirX;
    camera->wallX -= floor((camera->wallX));
	drawFloorAndCeiling(data,x, drawStart, drawEnd);
	draw_textureLine(drawStart, drawEnd, data, camera, x);
	return (SUCCESS);
}