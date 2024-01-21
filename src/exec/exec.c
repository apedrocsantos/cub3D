/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 20:27:52 by anda-cun          #+#    #+#             */
/*   Updated: 2024/01/21 20:08:38 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static int	event_handler(t_data *data)
{
	mlx_loop_hook(data->mlx, render_map_all, data);
	mlx_hook(data->win, 2, (1L << 0), &key_func, data);
	mlx_hook(data->win, 17, 0, &close_success, data);
	mlx_loop(data->mlx);
	return (SUCCESS);
}

int	exec(t_data *data)
{
	init_raycaster(data);
	init_frame(data);
	event_handler(data);
	return (SUCCESS);
}
