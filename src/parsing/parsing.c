/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 12:21:08 by anda-cun          #+#    #+#             */
/*   Updated: 2024/01/25 10:34:18 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*
Split string at commas. Check if nb_substrings is 3 (RGB). Check the values of
each string and assign them to the corresponding data field.
*/

t_rgb	*check_rgb(char **arr)
{
	int		i;
	t_rgb	*rgb;

	i = 0;
	while (arr[i])
		i++;
	if (i != 3 || check_rgb_values(arr) == FAILURE)
	{
		print_error("Invalid RGB values.", NULL);
		free_str_arr(arr);
		return (NULL);
	}
	rgb = malloc(sizeof(t_rgb));
	if (!rgb)
		return (NULL);
	rgb->red = ft_atoi(arr[0]);
	rgb->green = ft_atoi(arr[1]);
	rgb->blue = ft_atoi(arr[2]);
	free_str_arr(arr);
	return (rgb);
}

/*
 *Ignore spaces, check for multiple strings, if just one string,
	assign it to corresponding field.
 */

int	check_path(t_data *data, char *str, int dir)
{
	char	*new;
	int		i;

	i = 0;
	new = ft_strtrim(str, "\f\r\t\v ");
	if (!new)
		return (print_error("Empty path.", NULL));
	while (new[i] && !ft_strchr("\f\r\t\v ", new[i]))
		i++;
	if (!new[i])
	{
		if (check_file(new))
		{
			free(new);
			return (FAILURE);
		}
		data->cardinal_image[dir].path = new;
		return (SUCCESS);
	}
	free(new);
	return (print_error("Invalid path:", str));
}

int	parse_line(t_data *data, char *line)
{
	if (!ft_strncmp(line, "NO ", 3) && !data->cardinal_image[NORTH].path)
		return (check_path(data, &line[3], NORTH));
	else if (!ft_strncmp(line, "SO ", 3) && !data->cardinal_image[SOUTH].path)
		return (check_path(data, &line[3], SOUTH));
	else if (!ft_strncmp(line, "WE ", 3) && !data->cardinal_image[WEST].path)
		return (check_path(data, &line[3], WEST));
	else if (!ft_strncmp(line, "EA ", 3) && !data->cardinal_image[EAST].path)
		return (check_path(data, &line[3], EAST));
	else if (!ft_strncmp(line, "F ", 2) && !data->floor)
	{
		data->floor = check_rgb(ft_split(&line[2], ','));
		if (!data->floor)
			return (FAILURE);
	}
	else if (!ft_strncmp(line, "C ", 2) && !data->ceiling)
	{
		data->ceiling = check_rgb(ft_split(&line[2], ','));
		if (!data->ceiling)
			return (FAILURE);
	}
	else
		return (print_error("Duplicate values.", NULL));
	return (SUCCESS);
}

/**
 * Check each line for "NO ", "SO ", "EA ", "WE ", "F " and "C ", in any order.
 * If a different string is found and one or more of the fields is empty,
	returns error.
 * Else, all fields are present, and returns 2.
 */

int	check_line(t_data *data, char *line, t_cardinal_image *img)
{
	int	i;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	if (!line[i])
		return (SUCCESS);
	if (!strncmp(&line[i], "NO ", 3) || !strncmp(&line[i], "SO ", 3)
		|| !strncmp(&line[i], "WE ", 3) || !strncmp(&line[i], "EA ", 3)
		|| !strncmp(&line[i], "F ", 2) || !strncmp(&line[i], "C ", 2))
		return (parse_line(data, &line[i]));
	if (!img[NORTH].path || !img[SOUTH].path || !img[EAST].path
		|| !img[WEST].path || !data->ceiling || !data->floor)
		return (print_error("Missing data. Try again.", NULL));
	return (2);
}

/*
 * Reads each line of the cub file.
 * check_line function checks if NO, SO, WE, EA, F and C exist and stores them.
 * If all values are valid, check_line returns 2, and get_map begins.
 */
int	read_cub(t_data *data, char *line)
{
	int		a;

	if (!line)
		return (print_error("Empty file.", NULL));
	while (line)
	{
		a = check_line(data, line, data->cardinal_image);
		if (a == 2)
		{
			if (get_map(line, data, ft_strdup(line)) == FAILURE)
			{
				close(data->fd);
				return (1);
			}
		}
		if (a != 2)
			free(line);
		if (a != 0)
		{
			close(data->fd);
			return (a);
		}
		line = get_next_line(data->fd);
	}
	return (print_error("File is incomplete.", NULL));
}
