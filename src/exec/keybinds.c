#include "../includes/cub3D.h"

int moved(t_data *data, int pressed_key)
{
	if (validMove(data, pressed_key))
		return (FAILURE);
	if (pressed_key == W)
	{
		data->player.px+=data->player.pdx * PLAYER_SPEED;
		data->player.py+=data->player.pdy * PLAYER_SPEED;
	}
	else if (pressed_key == S)
	{
		data->player.px-=data->player.pdx * PLAYER_SPEED;
		data->player.py-=data->player.pdy * PLAYER_SPEED;
	}
	else if (pressed_key == A)
	{
		data->player.px -= data->player.planeX * PLAYER_SPEED;
        data->player.py -= data->player.planeY * PLAYER_SPEED;
	}
	else if (pressed_key == D)
	{
		data->player.px += data->player.planeX * PLAYER_SPEED;
        data->player.py += data->player.planeY * PLAYER_SPEED;
	}
	else
		return (FAILURE);
	return (SUCCESS);
}

int rotate(t_data *data, int pressed_key)
{
	if (pressed_key == LEFT)
		data->player.pa+=CAMERA_SPEED;
	else if (pressed_key == RIGHT)
		data->player.pa-=CAMERA_SPEED;
	else
		return (FAILURE);
	data->player.pa = FixAng(data->player.pa);
	data->player.planeX = cos(degToRad((data->player.pa - 90)));
	data->player.planeY = sin((degToRad(data->player.pa - 90)));
	data->player.pdx = cos(degToRad(data->player.pa));
	data->player.pdy = sin(degToRad(data->player.pa));
	return (SUCCESS);
}

int	key_func(int key, t_data *data)
{
	if (key == XK_Escape)
		close_success(data);
	if (key == XK_w || key == XK_Up)
		moved(data, W);
    else if (key == XK_s || key == XK_Down)
		moved(data, S);
	else if (key == XK_a)
		moved(data, A);
	else if (key == XK_d)
		moved(data, D);
	else if (key == XK_Left)
		rotate(data, LEFT);
    else if (key == XK_Right)
		rotate(data, RIGHT);
	else
		return (FAILURE);
	return (SUCCESS);
}

int	close_window(t_data *data, char *error, int rtn)
{
	if (error)
		ft_putendl_fd(error, 2);
	mlx_destroy_image(data->mlx, data->current_img.img);
	mlx_destroy_image(data->mlx, data->cardinal_image[NORTH].img);
	mlx_destroy_image(data->mlx, data->cardinal_image[SOUTH].img);
	mlx_destroy_image(data->mlx, data->cardinal_image[EAST].img);
	mlx_destroy_image(data->mlx, data->cardinal_image[WEST].img);
	if (data->mlx != NULL && data->win != NULL)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	free_data(data);
	ft_printf("Program closed by user!\n");
	exit(rtn);
}

int	close_success(t_data *data)
{
	close_window(data, NULL, SUCCESS);
	return (SUCCESS);
}