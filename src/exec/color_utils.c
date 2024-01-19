#include "../includes/cub3D.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	get_img_color(t_cardinal_image img, t_player *pos)
{
	// printf("%f %f\n", pos->px, pos->py);
	if (pos->px >= 0 && pos->px < img.width
		&& pos->py >= 0 && pos->py < img.height)
	{
		return (*(int*)(img.addr
			+ (4 * img.width * (int)pos->py)
			+ (4 * (int)pos->px)));
	}
	// printf("Error\n");
	return (0x0);
}
