/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 22:45:53 by anda-cun          #+#    #+#             */
/*   Updated: 2024/01/24 18:08:34 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	find_chars(char *str, char *to_find)
{
	int	i;
	int	j;

	i = -1;
	while (str[++i])
	{
		j = -1;
		while (to_find[++j])
		{
			if (str[i] == to_find[j])
				break ;
		}
		if (!to_find[j])
			return (FAILURE);
	}
	return (SUCCESS);
}

/**
 * Checks if first line and last line have chars different than '1' and ' '
 * While looping each line
 * 		Checks if first char is different than '1' and ' '
 *		If current char is space, check next, previous,
			above and below character. If they are not '1', returns error.
 */

int	map_check(t_data *data, char **map, int i, int j)
{
	while (map[++i])
	{
		if (i == 0 || i == data->nb_of_map_lines - 1)
			if (find_chars(map[i], "1 "))
				return (print_error("Invalid map: map is open.", NULL));
		j = -1;
		while (map[i][++j])
		{
			if (j == 0 && (map[i][j] != '1') && (map[i][j] != ' '))
				return (print_error("Invalid map: map is open.", NULL));
			if (!map[i][j + 1] && (map[i][j] != '1') && (map[i][j] != ' '))
				return (print_error("Invalid map: map is open.", NULL));
			if ((ft_isspace(map[i][j]) && j < (int)ft_strlen(map[i])
				&& map[i][j + 1] && !ft_strchr("1 ", map[i][j
						+ 1])) || (ft_isspace(map[i][j]) && j > 0
					&& map[i][j - 1] && !ft_strchr("1 ", map[i][j
						- 1])) || (ft_isspace(map[i][j])
					&& i < data->nb_of_map_lines - 1 && map[i + 1][j]
					&& !ft_strchr("1 ", map[i + 1][j]))
				|| (ft_isspace(map[i][j]) && i > 0 && map[i - 1][j]
					&& !ft_strchr("1 ", map[i - 1][j])))
				return (print_error("Invalid map: map is open.", NULL));
		}
	}
	return (0);
}

/**
 * Reopens the .cub file and finds the first line of the map.
 * Then adds each line to the string array.
 */
void	store_map(char *first_line, t_data *data)
{
	char	*line;
	int		i;
	int		j;
	int		fd;

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
}

/**
 * Creates array of strings to store map,
	with max line length of map fond previously.
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
 * If line contains valid characters, increment number of lines.
 * If current line length > previous line length, increase line length.
 */

int	get_map(char *line, t_data *data, char *first_line)
{
	int	line_len;

	data->nb_of_map_lines = 0;
	line_len = 0;
	while (line)
	{
		if (valid_map_line(line))
		{
			free(first_line);
			free(line);
			return (1);
		}
		data->nb_of_map_lines++;
		if ((int)ft_strlen(line) > line_len)
			line_len = ft_strlen(line);
		free(line);
		line = get_next_line(data->fd);
	}
	init_data_map(data, data->nb_of_map_lines, line_len, first_line);
	return (0);
}
