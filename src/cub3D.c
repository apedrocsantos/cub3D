/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:39:53 by anda-cun          #+#    #+#             */
/*   Updated: 2024/01/24 18:15:35 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <sys/types.h>
#include <sys/wait.h>

void	init_data(t_data *data, char *file_path)
{
	data->file = file_path;
	data->ceiling = NULL;
	data->floor = NULL;
	data->map = NULL;
	data->cardinal_image = ft_calloc(4, sizeof(t_cardinal_image));
	data->cardinal_image[NORTH].path = NULL;
	data->cardinal_image[SOUTH].path = NULL;
	data->cardinal_image[EAST].path = NULL;
	data->cardinal_image[WEST].path = NULL;
}

int	parsing(t_data *data)
{
	if (read_cub(data, get_next_line(data->fd)) != 2)
		return (FAILURE);
	if (map_check(data, data->map, -1, -1))
		return (FAILURE);
	return (SUCCESS);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
		return (print_error("Try ./cub3D path/to/map.cub", NULL));
	if (check_ext(av[1], ".cub"))
		return (1);
	data.fd = open(av[1], O_RDONLY);
	if (data.fd < 0)
		return (print_error("Error opening file.", NULL));
	init_data(&data, av[1]);
	if (parsing(&data) == FAILURE)
	{
		free_data(&data);
		return (FAILURE);
	}
	exec(&data);
	free_data(&data);
	return (SUCCESS);
}
