/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   etc_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:37:55 by anda-cun          #+#    #+#             */
/*   Updated: 2024/01/19 20:22:15 by ubuntu           ###   ########.fr       */
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
