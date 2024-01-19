/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:37:55 by anda-cun          #+#    #+#             */
/*   Updated: 2023/11/13 15:34:42 by anda-cun         ###   ########.fr       */
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

int	check_ext(char *str, char *ext)
{
	int	i;

	i = 0;
	while (!ft_isalnum(str[i]))
		i++;
	if (ft_strchr(&str[i], '.'))
		if (!strncmp(ft_strchr(&str[i], '.'), ext, 5))
			return (0);
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
	if (data->NO)
		free(data->NO);
	if (data->SO)
		free(data->SO);
	if (data->WE)
		free(data->WE);
	if (data->EA)
		free(data->EA);
	if (data->C)
		free(data->C);
	if (data->F)
		free(data->F);
	if (data->map)
		free_map(data->map);
}

void	print_data(t_data *data)
{
	int	i;

	i = 0;
	printf("NO: {%s}\n", data->NO);
	printf("SO: {%s}\n", data->SO);
	printf("WE: {%s}\n", data->WE);
	printf("EA: {%s}\n", data->EA);
	if (data->F)
		printf("F: {%d,%d,%d}\n", data->F->R, data->F->G, data->F->B);
	if (data->C)
		printf("C: {%d,%d,%d}\n", data->C->R, data->C->G, data->C->B);
	if (data->map && data->map[i])
	{
		while (data->map[i])
			printf("{%s}\n", data->map[i++]);
	}
}
