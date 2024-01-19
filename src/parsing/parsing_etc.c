/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_etc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 22:14:26 by anda-cun          #+#    #+#             */
/*   Updated: 2024/01/19 20:17:42 by ubuntu           ###   ########.fr       */
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

int	check_xpm(t_cardinal_image *img)
{
	int	fd;

	fd = open(img[NORTH].path, O_RDONLY);
	if (fd != -1)
		close(fd);
	else
		return (1);
	fd = open(img[SOUTH].path, O_RDONLY);
	if (fd != -1)
		close(fd);
	else
		return (1);
	fd = open(img[EAST].path, O_RDONLY);
	if (fd != -1)
		close(fd);
	else
		return (1);
	fd = open(img[WEST].path, O_RDONLY);
	if (fd != -1)
		close(fd);
	else
		return (1);
	return (0);
}

int	check_extensions(t_cardinal_image *img)
{
	if (check_xpm(img))
		return (print_error("Can't access xpm file.", NULL));
	if (check_ext(img[NORTH].path, ".xpm"))
		return (print_error("Wrong file extension: ", img[NORTH].path));
	if (check_ext(img[SOUTH].path, ".xpm"))
		return (print_error("Wrong file extension: ", img[SOUTH].path));
	if (check_ext(img[WEST].path, ".xpm"))
		return (print_error("Wrong file extension: ", img[WEST].path));
	if (check_ext(img[EAST].path, ".xpm"))
		return (print_error("Wrong file extension: ", img[EAST].path));
	return (0);
}

void	free_data(t_data *data)
{
	if (data->cardinal_image[NORTH].path)
		free(data->cardinal_image[NORTH].path);
	if (data->cardinal_image[SOUTH].path)
		free(data->cardinal_image[SOUTH].path);
	if (data->cardinal_image[WEST].path)
		free(data->cardinal_image[WEST].path);
	if (data->cardinal_image[EAST].path)
		free(data->cardinal_image[EAST].path);
	if (data->cardinal_image)
		free(data->cardinal_image);
	if (data->ceiling)
		free(data->ceiling);
	if (data->floor)
		free(data->floor);
	if (data->map)
		free_map(data->map);
}
