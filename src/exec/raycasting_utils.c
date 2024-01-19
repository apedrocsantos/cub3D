#include "../includes/cub3D.h"


void searchHit(int hit, t_camera *camera, t_data *data)
{
    while (hit == 0)
    {
        if (camera->sideDistX < camera->sideDistY)
        {
            camera->sideDistX += camera->deltaDistX;
            camera->mapX += camera->stepX;
            camera->side = 0;
        }
        else
        {
            camera->sideDistY += camera->deltaDistY;
            camera->mapY += camera->stepY;
            camera->side = 1;
        }
        if (data->map[camera->mapX][camera->mapY] && 
                data->map[camera->mapX][camera->mapY] == '1') {
            hit = 1;
        }
    }
    if (camera->side == 0)
        camera->perpWallDist = (camera->sideDistX - camera->deltaDistX);
    else
        camera->perpWallDist = (camera->sideDistY - camera->deltaDistY);
}

void  calcSideDist(t_camera *camera, t_data *data)
{
    if (camera->rayDirX < 0)
    {
        camera->stepX = -1;
        camera->sideDistX = (data->player.px - camera->mapX) * camera->deltaDistX;
    }
    else
    {
        camera->stepX = 1;
        camera->sideDistX = (camera->mapX + 1.0 - data->player.px) * camera->deltaDistX;
    }
    if (camera->rayDirY < 0)
    {
        camera->stepY = -1;
        camera->sideDistY = (data->player.py - camera->mapY) * camera->deltaDistY;
    }
    else
    {
        camera->stepY = 1;
        camera->sideDistY = (camera->mapY + 1.0 - data->player.py) * camera->deltaDistY;
    }
}