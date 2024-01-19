/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 20:28:01 by anda-cun          #+#    #+#             */
/*   Updated: 2024/01/19 20:44:19 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

double	absolute_of(double number)
{
	if (number < 0)
		return (number * (-1));
	return (number);
}

double	square_of(double number)
{
	return (number * number);
}

double	deg_to_rad(double a)
{
	return ((double)(a / 180.00) *M_PI);
}

double	fix_ang(double a)
{
	if (a > 359)
		a -= 360;
	else if (a < 0)
		a += 360;
	return (a);
}
