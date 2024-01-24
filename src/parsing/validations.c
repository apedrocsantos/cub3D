/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validations.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 12:21:00 by anda-cun          #+#    #+#             */
/*   Updated: 2024/01/24 17:32:14 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/**
 * Check first char for digit or '+'.
 * Check if there are no more chars after space(s).
 * Check if all the other chars are numbers.
 */

int	valid_number(char *str)
{
	if (!str)
		return (FAILURE);
	if (*str == '+')
		str++;
	while (str && ft_isdigit(*str))
		str++;
	while (str && ft_isspace(*str))
		str++;
	if (*str)
		return (FAILURE);
	return (SUCCESS);
}

/**
* Ignore spaces. Check if string is a valid number
* between 0 and 255.
 */

int	check_rgb_values(char **arr)
{
	int	i;
	int	j;

	i = -1;
	while (arr[++i])
	{
		j = 0;
		while (ft_isspace(arr[i][j]))
			j++;
		if (!arr[i][j])
			return (FAILURE);
		if (valid_number(&arr[i][j]) || ft_atoi(&arr[i][j]) > 255)
			return (FAILURE);
	}
	return (SUCCESS);
}

/**
 * Checks if line is valid (char "\f\r\t\v ").
 */

int	valid_map_line(char *line)
{
	int		i;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	if (!line[i])
		return (print_error("Invalid map: empty line.", NULL));
	i = -1;
	while (line[++i])
		if (!ft_strchr("10NSWE ", line[i]))
			return (print_error("Invalid map: invalid character in map.",
					NULL));
	return (0);
}

int	check_ext(char *str, char *ext)
{
	if (ft_strchr(str, '.'))
		if (!strncmp(ft_strrchr(str, '.'), ext, 5))
			return (SUCCESS);
	return (print_error("Invalid file extension: ", str));
}

int	check_file(char *str)
{
	int	i;
	int	fd;

	i = NORTH;
	while (i <= SOUTH)
	{
		if (check_ext(str, ".xpm"))
			return (1);
		fd = open(str, O_RDONLY);
		if (fd != -1)
			close(fd);
		else
			return (print_error("Can't access xpm file ", str));
		i++;
	}
	return (0);
}
