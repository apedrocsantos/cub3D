/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 20:26:03 by anda-cun          #+#    #+#             */
/*   Updated: 2024/01/21 19:59:01 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

#define ERROR_CODE -1

void	leave_on_error(t_data *data, char *error_statement)
{
	print_error(error_statement, NULL);
	free_data(data);
	exit(ERROR_CODE);
}
