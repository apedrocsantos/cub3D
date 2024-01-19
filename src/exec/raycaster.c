/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 20:28:03 by anda-cun          #+#    #+#             */
/*   Updated: 2024/01/19 20:44:46 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	init_raycaster(t_data *data)
{
	if (data->player.direction == 'N')
		data->player.pa = (180);
	else if (data->player.direction == 'S')
		data->player.pa = (0);
	else if (data->player.direction == 'E')
		data->player.pa = (90);
	else if (data->player.direction == 'W')
		data->player.pa = (270);
	else
		leave_on_error(data, "Invalid player direction");
	data->player.pdx = cos(deg_to_rad(data->player.pa));
	data->player.plane_x = cos(deg_to_rad(data->player.pa - (90)));
	data->player.plane_y = sin(deg_to_rad(data->player.pa - (90)));
	data->player.pdy = sin(deg_to_rad(data->player.pa));
	return (SUCCESS);
}
