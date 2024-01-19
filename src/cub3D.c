/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:39:53 by anda-cun          #+#    #+#             */
/*   Updated: 2023/11/17 15:54:55 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <sys/types.h>
#include <sys/wait.h>

void	init_data(t_data *data)
{
	data->EA = NULL;
	data->NO = NULL;
	data->SO = NULL;
	data->WE = NULL;
	data->C = NULL;
	data->F = NULL;
	data->map = NULL;
}

int	main(int ac, char **av)
{
	t_data	data;
	int fd;

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
	if (check_extensions(&data) || map_check(&data, -1, -1))
	{
		free_data(&data);
		return (1);
	}
	exec(&data);
	free_data(&data);
}
