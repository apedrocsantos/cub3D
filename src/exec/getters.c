/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 20:27:54 by anda-cun          #+#    #+#             */
/*   Updated: 2024/01/23 18:08:43 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	gettex_x(t_data *data, t_camera *camera)
{
	int	tex_x;

	tex_x = (int)(camera->wall_x * (double)(data->cardinal_image[0].width));
	if (camera->side == 0 && camera->ray_dir_x > 0)
		tex_x = data->cardinal_image[0].width - tex_x - 1;
	if (camera->side == 1 && camera->ray_dir_y < 0)
		tex_x = data->cardinal_image[0].width - tex_x - 1;
	return (tex_x);
}

int	get_img_direction(t_data *data, t_camera *camera)
{
	if (camera->side == 1)
	{
		if (data->player.py > camera->map_y)
			return (WEST);
		else
			return (EAST);
	}
	else
	{
		if (data->player.px > camera->map_x)
			return (NORTH);
		else
			return (SOUTH);
	}
	return (FAILURE);
}

void	get_playermap_start_pos(t_data *data)
{
	int	xi;
	int	yi;
	int	match;

	xi = -1;
	match = 0;
	while (data->map[++xi] != NULL)
	{
		yi = -1;
		while (data->map[xi][++yi] != '\0')
		{
			if (data->map[xi][yi] == 'N' || data->map[xi][yi] == 'S'
				|| data->map[xi][yi] == 'W' || data->map[xi][yi] == 'E')
			{
				if (match == 1)
					leave_on_error(data, "Multiple player initial positions.");
				data->player.direction = data->map[xi][yi];
				data->player.px = (double)(xi + 0.5);
				data->player.py = (double)(yi + 0.5);
				match = 1;
			}
		}
	}
	if (match == 0)
		leave_on_error(data, "Can't find player.");
}
