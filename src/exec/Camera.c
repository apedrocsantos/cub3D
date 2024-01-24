/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 20:27:42 by anda-cun          #+#    #+#             */
/*   Updated: 2024/01/23 18:29:02 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	check_squares(t_data *data, double x, double y)
{
	int	a;
	int	b;

	a = (int)x;
	b = (int)y;
	if (floor(data->player.px) < floor(x + 0.1))
		a = floor(data->player.px) + 1;
	else if (floor(data->player.px) > floor(x + 0.1))
		a = floor(data->player.px) - 1;
	if (floor(data->player.py) != floor(y + 0.1))
		b = floor(data->player.py) + 1;
	else if (floor(data->player.py) != floor(y + 0.1))
		b = floor(data->player.py) - 1;
	if (data->map[a][b] == '1')
		return (FAILURE);
	return (SUCCESS);
}

int	valid_move(t_data *data, int pressed_key)
{
	double	x;
	double	y;

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
		x = (data->player.px - data->player.plane_x * PLAYER_SPEED);
		y = (data->player.py - data->player.plane_y * PLAYER_SPEED);
	}
	else if (pressed_key == D)
	{
		x = (data->player.px + data->player.plane_x * PLAYER_SPEED);
		y = (data->player.py + data->player.plane_y * PLAYER_SPEED);
	}
	return (check_squares(data, x, y));
}

void	render_map(t_data *data)
{
	t_camera	camera;

	camera.x = -1;
	while (++camera.x < INITIAL_XSIZE)
	{
		camera.camera_x = 2 * camera.x / (double)INITIAL_XSIZE - 1;
		camera.ray_dir_x = data->player.pdx + data->player.plane_x
			* camera.camera_x;
		camera.ray_dir_y = data->player.pdy + data->player.plane_y
			* camera.camera_x;
		camera.map_x = (int)(data->player.px);
		camera.map_y = (int)(data->player.py);
		if (camera.ray_dir_x == 0)
			camera.delta_dist_x = 1e30;
		else
			camera.delta_dist_x = fabs(1 / camera.ray_dir_x);
		if (camera.ray_dir_y == 0)
			camera.delta_dist_y = 1e30;
		else
			camera.delta_dist_y = fabs(1 / camera.ray_dir_y);
		calc_side_dist(&camera, data);
		search_hit(0, &camera, data);
		camera.line_height = (INITIAL_YSIZE / camera.perp_wall_dist);
		draw_stuff(data, &camera);
	}
}
