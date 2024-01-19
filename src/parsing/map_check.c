/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 22:45:53 by anda-cun          #+#    #+#             */
/*   Updated: 2023/11/16 12:55:05 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	get_map(char *line, int fd, t_data *data, char *first_line)
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
		line = get_next_line(fd);
	}
	free (line);
	init_data_map(data, data->nb_of_map_lines, line_len, first_line);
	return (0);
}

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
			return (1);
	}
	return (0);
}

/**
 * Checks if first line and last line have chars different than '1' and ' '
 * While looping each line
 * 		Checks if first char is different than '1' and ' '
 *
*/

int	map_check(t_data *data, int i, int j)
{
	while (data->map[++i])
	{
		if (i == 0 || i == data->nb_of_map_lines - 1)
			if (find_chars(data->map[i], "1 "))
				return (print_error("Invalid map. Check line: ", data->map[i]));
		j = -1;
		while (data->map[i][++j])
		{
			if (j == 0 && (data->map[i][j] != '1') && (data->map[i][j] != ' '))
				return (print_error("Invalid map. Check line: ", data->map[i]));
			if ((data->map[i][j] == ' ' && j < (int)ft_strlen(data->map[i])
				&& data->map[i][j + 1] && !ft_strchr("1 ", data->map[i][j
					+ 1])) || (data->map[i][j] == ' ' && j > 0
				&& data->map[i][j - 1] && !ft_strchr("1 ", data->map[i][j
					- 1])) || (data->map[i][j] == ' '
				&& i < data->nb_of_map_lines - 1 && data->map[i + 1][j]
				&& !ft_strchr("1 ", data->map[i + 1][j]))
				|| (data->map[i][j] == ' ' && i > 0 && data->map[i - 1][j]
					&& !ft_strchr("1 ", data->map[i - 1][j])))
				return (print_error("Invalid map. Check line: ", data->map[i]));
		}
	}
	return (0);
}
