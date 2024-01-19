/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:39:53 by anda-cun          #+#    #+#             */
/*   Updated: 2024/01/19 20:17:42 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <sys/types.h>
#include <sys/wait.h>

void	init_data(t_data *data)
{
	data->ceiling = NULL;
	data->floor = NULL;
	data->map = NULL;
	data->cardinal_image = ft_calloc(4, sizeof(t_cardinal_image));
	data->cardinal_image[NORTH].path = NULL;
	data->cardinal_image[SOUTH].path = NULL;
	data->cardinal_image[EAST].path = NULL;
	data->cardinal_image[WEST].path = NULL;
}

int	main(int ac, char **av)
{
	t_data	data;
	int		fd;

	if (ac != 2)
		return (print_error("Try ./cub3D path/to/map.cub", NULL));
	init_data(&data);
	if (check_ext(av[1], ".cub"))
		return (print_error("Invalid file extension.", NULL));
	data.file = av[1];
	fd = open(data.file, O_RDONLY);
	if (read_cub(&data, fd) != 2)
	{
		close(fd);
		free_data(&data);
		return (1);
	}
	close(fd);
	if (check_extensions(data.cardinal_image) || map_check(&data, -1, -1))
	{
		free_data(&data);
		return (1);
	}
	exec(&data);
	free_data(&data);
}
