/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 20:26:03 by anda-cun          #+#    #+#             */
/*   Updated: 2024/01/19 20:29:44 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

#define ERROR_CODE -1

void	leave_on_error(t_data *data, char *error_statement)
{
	printf("[ERROR_HANDLER]:%d %s\n", data->map[0][0], error_statement);
	exit(ERROR_CODE);
}
