/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 20:28:03 by anda-cun          #+#    #+#             */
/*   Updated: 2024/01/21 20:09:25 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	init_raycaster(t_data *data)
{
	get_playermap_start_pos(data);
	if (data->player.direction == 'N')
		data->player.pa = (180);
	else if (data->player.direction == 'S')
		data->player.pa = (0);
	else if (data->player.direction == 'E')
		data->player.pa = (90);
	else if (data->player.direction == 'W')
		data->player.pa = (270);
	data->player.pdx = cos(deg_to_rad(data->player.pa));
	data->player.plane_x = cos(deg_to_rad(data->player.pa - (90)));
	data->player.plane_y = sin(deg_to_rad(data->player.pa - (90)));
	data->player.pdy = sin(deg_to_rad(data->player.pa));
	return (SUCCESS);
}
