/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   etc_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:37:55 by anda-cun          #+#    #+#             */
/*   Updated: 2024/01/24 12:30:49 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	print_error(char *str, char *str2)
{
	ft_putendl_fd("Error", 2);
	ft_putstr_fd(str, 2);
	if (str2)
		ft_putstr_fd(str2, 2);
	ft_putstr_fd("\n", 2);
	return (1);
}

void	free_str_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	free_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		free(map[i++]);
	free(map);
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
