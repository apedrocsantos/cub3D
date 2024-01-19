/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 22:11:40 by anda-cun          #+#    #+#             */
/*   Updated: 2023/11/16 12:54:48 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	valid_number(char *str)
{
	int	i;

	i = 0;
	if (str && *str && (ft_isdigit(str[0]) || str[0] == '+'))
	{
		while (str[++i])
			if (!ft_isdigit(str[i]))
				return (0);
	}
	else
		return (0);
	return (1);
}

int	check_values(char **arr)
{
	int		i;
	char	*check;

	i = -1;
	while (arr[++i])
	{
		check = ft_strtrim(arr[i], " ");
		if (!valid_number(check))
		{
			free(check);
			return (0);
		}
		free(check);
	}
	return (1);
}

int	store_map(char *first_line, t_data *data)
{
	int		fd;
	char	*line;
	int		i;
	int		j;

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
	return (0);
}

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

int	valid_line(char *line)
{
	int		i;
	char	*check_empty;

	i = -1;
	check_empty = ft_strtrim(line, "\f\r\t\v ");
	if (!check_empty)
		return (print_error("Invalid character in map.", NULL));
	free(check_empty);
	while (line[++i])
		if (!ft_strchr("10NSWE ", line[i]))
			return (print_error("Invalid character in map.", NULL));
	return (0);
}
