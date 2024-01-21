/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 22:11:40 by anda-cun          #+#    #+#             */
/*   Updated: 2024/01/21 23:33:49 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/**
 * get length of string until '\0' or space.
 * Check if there are no more chars after space(s).
 * legth has to be <= 4 (to include possible '+').
 * Check first char for digit or '+'.
 * Check if all the other chars are numbers.
*/

int	valid_number(char *str)
{
	int	i;
	int nb_len;

	i = -1;
	nb_len = 0;
	if (!str)
		return (ERROR);
	while (str[nb_len] && !ft_isspace(str[nb_len]))
		nb_len++;
	i = nb_len;
	while (ft_isspace(str[i]))
		i++;
	if (str[i])
		return (ERROR);
	i = -1;
	if (nb_len <= 4 && (ft_isdigit(str[0]) || str[0] == '+'))
	{
		if (str[0] == '+')
			i++;
		while (++i < nb_len)
			if (!ft_isdigit(str[i]))
				return (ERROR);
	}
	else
		return (ERROR);
	return (SUCCESS);
}

/**
 * Ignore spaces. Check if string is a valid positive number and smaller than 255.
*/

int	check_values(char **arr)
{
	int		i;
	int		j;

	i = -1;
	while (arr[++i])
	{
		j = 0;
		while(ft_isspace(arr[i][j]))
			j++;
		if (!arr[i][j])
			return (print_error("Missing RGB values.", NULL));
		if (valid_number(&arr[i][j]) || ft_atoi(&arr[i][j]) > 255)
			return (print_error("Invalid RGB values.", NULL));
	}
	return (SUCCESS);
}


/**
 * Reopens the .cub file and finds the first line of the map.
 * Then adds each line to the string array.
*/
int	store_map(char *first_line, t_data *data)
{
	char	*line;
	int		i;
	int		j;
	int fd;

	i = 0;
	fd = open(data->file, O_RDONLY);
	line = get_next_line(fd);
	while (line && ft_strncmp(line, first_line, ft_strlen(first_line)))
	{
		free(line);
		line = get_next_line(fd);
	}
	free(first_line);
	while (line && *line)
	{
		j = -1;
		while (line[++j])
			data->map[i][j] = line[j];
		i++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (0);
}

/**
 * Creates array of strings to store map, with max line length of map fond previously.
 * Fills empty array with spaces.
*/

void	init_data_map(t_data *data, int line_nb, int line_len, char *first_line)
{
	int	i;

	i = -1;
	data->map = ft_calloc(line_nb + 1, sizeof(char **));
	while (++i < line_nb)
	{
		data->map[i] = ft_calloc(line_len + 1, sizeof(char));
		ft_memset(data->map[i], ' ', line_len);
	}
	store_map(first_line, data);
}

/**
 * Checks if line is valid (char "\f\r\t\v ").
*/

int	valid_line(char *line)
{
	int		i;
	char	*check_empty;

	i = -1;
	check_empty = ft_strtrim(line, "\f\r\t\v ");
	if (!check_empty)
		return (print_error("Invalid map: empty line.", NULL));
	free(check_empty);
	while (line[++i])
		if (!ft_strchr("10NSWE ", line[i]))
			return (print_error("Invalid map: invalid character in map.", NULL));
	return (0);
}
