/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 20:27:46 by anda-cun          #+#    #+#             */
/*   Updated: 2024/01/19 20:29:30 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	get_img_color(t_cardinal_image img, t_player *pos)
{
	if (pos->px >= 0 && pos->px < img.width && pos->py >= 0
		&& pos->py < img.height)
	{
		return (*(int *)(img.addr + (4 * img.width * (int)pos->py) + (4
				* (int)pos->px)));
	}
	return (0x0);
}
