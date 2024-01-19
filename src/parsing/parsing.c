/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 12:21:08 by anda-cun          #+#    #+#             */
/*   Updated: 2024/01/19 20:47:22 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_rgb	*check_rgb(char *str)
{
	int		i;
	char	**arr;
	t_rgb	*rgb;

	i = 0;
	arr = ft_split(str, ',');
	while (arr[i])
		i++;
	if (i != 3 || !check_values(arr))
	{
		free_str_arr(arr);
		return (NULL);
	}
	rgb = malloc(sizeof(t_rgb));
	rgb->red = ft_atoi(arr[0]);
	rgb->green = ft_atoi(arr[1]);
	rgb->blue = ft_atoi(arr[2]);
	free_str_arr(arr);
	return (rgb);
}

char	*check_path(char *str)
{
	char	*new;
	int		i;

	i = 0;
	new = ft_strtrim(str, "\f\r\t\v ");
	while (new[i] && !ft_strchr("\f\r\t\v ", new[i]))
		i++;
	while (new[i] && new[i] == ' ')
		i++;
	if (!new[i])
		return (new);
	free(new);
	print_error("Invalid path.", NULL);
	return (NULL);
}

int	get_file_path(t_data *data, char *line)
{
	if (!ft_strncmp(line, "NO ", 3) && !data->cardinal_image[NORTH].path)
		data->cardinal_image[NORTH].path = check_path(&line[3]);
	else if (!ft_strncmp(line, "SO ", 3) && !data->cardinal_image[SOUTH].path)
		data->cardinal_image[SOUTH].path = check_path(&line[3]);
	else if (!ft_strncmp(line, "WE ", 3) && !data->cardinal_image[WEST].path)
		data->cardinal_image[WEST].path = check_path(&line[3]);
	else if (!ft_strncmp(line, "EA ", 3) && !data->cardinal_image[EAST].path)
		data->cardinal_image[EAST].path = check_path(&line[3]);
	else if (!ft_strncmp(line, "F ", 2) && !data->floor)
		data->floor = check_rgb(&line[2]);
	else if (!ft_strncmp(line, "C ", 2) && !data->ceiling)
		data->ceiling = check_rgb(&line[2]);
	else
	{
		print_error("Duplicate values.", NULL);
		return (1);
	}
	return (0);
}

int	check_line(t_data *data, char *line, t_cardinal_image *img)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i])
	{
		if (!strncmp(&line[i], "NO ", 3) || !strncmp(&line[i], "SO ", 3)
			|| !strncmp(&line[i], "WE ", 3) || !strncmp(&line[i], "EA ", 3)
			|| !strncmp(&line[i], "F ", 2) || !strncmp(&line[i], "C ", 2))
		{
			if (get_file_path(data, &line[i]))
				return (1);
		}
		else if (!img[NORTH].path || !img[SOUTH].path || !img[EAST].path
			|| !img[WEST].path || !data->ceiling || !data->floor)
			return (print_error("Invalid cub settings. Check rules.", NULL));
		else
			return (2);
	}
	return (0);
}

/*
 * Reads each line of the cub file.
 * check_line function checks if NO, SO< WE, EA, F and C exist and stores them.
 * If all values are valid, check_line returns 2, and get_map begins.
 */
int	read_cub(t_data *data, int fd)
{
	char	*line;
	int		a;

	line = open_cub(fd);
	if (!line)
		return (1);
	while (line)
	{
		a = check_line(data, line, data->cardinal_image);
		if (a == 2)
		{
			if (get_map(line, fd, data, ft_strdup(line)))
				return (1);
		}
		if (a != 2)
			free(line);
		if (a)
			return (a);
		line = get_next_line(fd);
	}
	return (0);
}
