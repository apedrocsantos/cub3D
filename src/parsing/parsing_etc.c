/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_etc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 22:14:26 by anda-cun          #+#    #+#             */
/*   Updated: 2023/11/13 11:47:46 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	*open_cub(int fd)
{
	char	*line;

	if (fd < 0)
	{
		print_error("Error opening file", NULL);
		return (NULL);
	}
	line = get_next_line(fd);
	if (!line)
	{
		print_error("Empty file.", NULL);
		return (NULL);
	}
	return (line);
}

int check_xpm(t_data *data)
{
	int fd;

	fd = open(data->NO, O_RDONLY);
	if (fd != -1)
		close(fd);
	else
		return (1);
	fd = open(data->SO, O_RDONLY);
	if (fd != -1)
		close(fd);
	else
		return (1);
	fd = open(data->EA, O_RDONLY);
	if (fd != -1)
		close(fd);
	else
		return (1);
	fd = open(data->WE, O_RDONLY);
	if (fd != -1)
		close(fd);
	else
		return (1);
	return(0);
}

int	check_extensions(t_data *data)
{
	if (check_xpm(data))
		return (print_error("Can't access xpm file.", NULL));
	if (check_ext(data->NO, ".xpm"))
		return (print_error("Wrong file extension: ", data->NO));
	if (check_ext(data->SO, ".xpm"))
		return (print_error("Wrong file extension: ", data->SO));
	if (check_ext(data->WE, ".xpm"))
		return (print_error("Wrong file extension: ", data->WE));
	if (check_ext(data->EA, ".xpm"))
		return (print_error("Wrong file extension: ", data->EA));
	return (0);
}
