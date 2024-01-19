/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 20:28:04 by anda-cun          #+#    #+#             */
/*   Updated: 2024/01/19 20:45:27 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	search_hit(int hit, t_camera *camera, t_data *data)
{
	while (hit == 0)
	{
		if (camera->side_dist_x < camera->side_dist_y)
		{
			camera->side_dist_x += camera->delta_dist_x;
			camera->map_x += camera->step_x;
			camera->side = 0;
		}
		else
		{
			camera->side_dist_y += camera->delta_dist_y;
			camera->map_y += camera->step_y;
			camera->side = 1;
		}
		if (data->map[camera->map_x][camera->map_y]
			&& data->map[camera->map_x][camera->map_y] == '1')
		{
			hit = 1;
		}
	}
	if (camera->side == 0)
		camera->perp_wall_dist = (camera->side_dist_x - camera->delta_dist_x);
	else
		camera->perp_wall_dist = (camera->side_dist_y - camera->delta_dist_y);
}

void	calc_side_dist(t_camera *camera, t_data *data)
{
	if (camera->ray_dir_x < 0)
	{
		camera->step_x = -1;
		camera->side_dist_x = (data->player.px - camera->map_x)
			* camera->delta_dist_x;
	}
	else
	{
		camera->step_x = 1;
		camera->side_dist_x = (camera->map_x + 1.0 - data->player.px)
			* camera->delta_dist_x;
	}
	if (camera->ray_dir_y < 0)
	{
		camera->step_y = -1;
		camera->side_dist_y = (data->player.py - camera->map_y)
			* camera->delta_dist_y;
	}
	else
	{
		camera->step_y = 1;
		camera->side_dist_y = (camera->map_y + 1.0 - data->player.py)
			* camera->delta_dist_y;
	}
}
