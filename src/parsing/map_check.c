/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 22:45:53 by anda-cun          #+#    #+#             */
/*   Updated: 2024/01/21 22:09:00 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/**
 * If line contains valid characters, increment number of lines.
 * If current line length > previous line length, increase line length.
*/

int	get_map(char *line, t_data *data, char *first_line)
{
	int		line_len;

	data->nb_of_map_lines = 0;
	line_len = 0;
	while (line)
	{
		if (valid_line(line))
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

/**
 * Checks if first line and last line have chars different than '1' and ' '
 * While looping each line
 * 		Checks if first char is different than '1' and ' '
 *		If current char is space, check next, previous, above and below character. If they are not '1', returns error.
*/

int	map_check(t_data *data, int i, int j)
{
	while (data->map[++i])
	{
		if (i == 0 || i == data->nb_of_map_lines - 1)
			if (ft_strchr("1 ", &data->map[i]))
				return (print_error("Invalid map: map is open.", NULL));
		j = -1;
		while (data->map[i][++j])
		{
			if (j == 0 && (data->map[i][j] != '1') && (data->map[i][j] != ' '))
				return (print_error("Invalid map: map is open.", NULL));
			if ((ft_isspace(data->map[i][j]) && j < (int)ft_strlen(data->map[i])
				&& data->map[i][j + 1] && !ft_strchr("1 ", data->map[i][j
					+ 1])) || (ft_isspace(data->map[i][j]) && j > 0
				&& data->map[i][j - 1] && !ft_strchr("1 ", data->map[i][j
					- 1])) || (ft_isspace(data->map[i][j])
				&& i < data->nb_of_map_lines - 1 && data->map[i + 1][j]
				&& !ft_strchr("1 ", data->map[i + 1][j]))
				|| (ft_isspace(data->map[i][j]) && i > 0 && data->map[i - 1][j]
					&& !ft_strchr("1 ", data->map[i - 1][j])))
				return (print_error("Invalid map: map is open.", NULL));
		}
	}
	return (0);
}
