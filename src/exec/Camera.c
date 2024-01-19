#include "../includes/cub3D.h"

int validMove(t_data *data, int pressed_key)
{
    double x;
    double y;

    if (pressed_key == W)
    {
        x = (data->player.px + data->player.pdx * PLAYER_SPEED);
        y = (data->player.py + data->player.pdy * PLAYER_SPEED);
    }
    else if (pressed_key == S)
    {
        x = (data->player.px - data->player.pdx * PLAYER_SPEED);
        y = (data->player.py - data->player.pdy * PLAYER_SPEED);
    }
    else if (pressed_key == A)
    {
        x = (data->player.px - data->player.planeX * PLAYER_SPEED);
        y = (data->player.py - data->player.planeY * PLAYER_SPEED);
    }
    else if (pressed_key == D)
    {
        x = (data->player.px + data->player.planeX * PLAYER_SPEED);
        y = (data->player.py + data->player.planeY * PLAYER_SPEED);
    }
    else
        return (FAILURE);
    if (data->map[(int)x][(int)y] != '1')
        return (SUCCESS);
    return (FAILURE);
}

void render_map(t_data *data)
{
    int x;
    int hit;
    t_camera    camera;
    
    x = -1;
    hit = 0;
    // draw_floor(data);
    // draw_sky(data);
    while (++x < INITIAL_XSIZE)
    {
        camera.cameraX = 2 * x / (double)INITIAL_XSIZE - 1;
        camera.rayDirX = data->player.pdx + data->player.planeX * camera.cameraX;
        camera.rayDirY = data->player.pdy + data->player.planeY * camera.cameraX;
        camera.mapX = (int)(data->player.px);
        camera.mapY = (int)(data->player.py);
        if (camera.rayDirX == 0)
            camera.deltaDistX = 1e30;
        else
            camera.deltaDistX = fabs(1 / camera.rayDirX);
        if (camera.rayDirY == 0)
            camera.deltaDistY = 1e30;
        else
            camera.deltaDistY = fabs(1 / camera.rayDirY);
        calcSideDist(&camera, data);
        searchHit(hit, &camera, data);
        camera.lineHeight = (INITIAL_YSIZE / camera.perpWallDist);
        draw_stuff(data, x, &camera);
    }
    draw_crosshair(data);
}
