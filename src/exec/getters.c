#include "../includes/cub3D.h"

int getTexX(t_data *data, t_camera *camera)
{
    int texX;

    texX = (int)(camera->wallX * (double)(data->cardinal_image[0].width));
    if(camera->side == 0 && camera->rayDirX > 0)
		texX = data->cardinal_image[0].width - texX - 1;
    if(camera->side == 1 && camera->rayDirY < 0)
		texX = data->cardinal_image[0].width - texX - 1;
    return (texX);
}

int getImgDirection(t_data *data, t_camera *camera)
{
    if (camera->side == 1)
    {
        if (data->player.py > camera->mapY)
            return WEST;
        else
            return EAST;
    }
    else
    {
        if (data->player.px > camera->mapX)
            return NORTH;
        else
            return SOUTH;
    }
    return FAILURE;
}

void get_playermap_start_pos(t_data *data)
{
    int xi;
    int yi;
    int match;

    xi = -1;
    yi = -1;
    match = 0;
    while (data->map[++xi] != NULL) /*Runs through the map file and if {N,S,W,E} saves coords and direction*/
    {
        while (data->map[xi][++yi] != '\0')
        {
            if (data->map[xi][yi] == 'N' || data->map[xi][yi] == 'S' 
                || data->map[xi][yi] == 'W' || data->map[xi][yi] == 'E')
            {
                if (match == 1)
                    leave_on_error(data, "Multiple player initial positions!");
                data->player.direction = data->map[xi][yi];
                data->player.px = (double) (xi + 0.5);
                data->player.py = (double) (yi + 0.5);
                match = 1;
            }
        }
        yi = -1;
    }
}