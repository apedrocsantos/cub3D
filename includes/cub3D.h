/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 10:28:42 by anda-cun          #+#    #+#             */
/*   Updated: 2023/11/17 15:57:51 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H

# define CUB3D_H

# define GAME_NAME "cub3d"
# define INITIAL_XSIZE 1920 //960
# define INITIAL_YSIZE 1080 //540
# define ERROR -1314
# define PLAYER_SPEED 0.1
#define CONSTANT_DISTANCE 0.5
# define CAMERA_SPEED 1.5
#define INVALID_POSITION -1

# include "../minilibx-linux/mlx.h"
# include "libft.h"
# include <X11/X.h>
# include <math.h>
# include <X11/keysym.h>
# include <stdio.h>
# include <stdlib.h>

enum					FINAL
{
	SUCCESS,
	FAILURE,
};

enum					CARDINAL
{
	NORTH,
	SOUTH,
	WEST,
	EAST,
};

enum					KEYS
{
	W,
	A,
	S,
	D,
	LEFT,
	RIGHT,
};

typedef struct s_camera
{
    double cameraX;
    double rayDirX;
    double rayDirY;
    int mapX;
    int mapY;
    double sideDistX;
    double sideDistY;
    double deltaDistX;
    double deltaDistY;
    double perpWallDist;
    int     stepX;
    int     stepY;
	int		side;
	double	wallX;
	double lineHeight;
}           t_camera;

typedef struct s_rgb
{
	int					R;
	int					G;
	int					B;
}						t_rgb;

typedef struct s_cardinal_image
{
	int					direction;
	char				*path;
	void				*img;
	char				*addr;
	int					bits_per_pixel;
	int					line_length;
	int					endian;
	int					width;
	int					height;
}						t_cardinal_image;

typedef struct s_main_image
{
	void				*img;
	char				*addr;
	int					bits_per_pixel;
	int					line_length;
	int					endian;
}						t_main_image;

typedef struct s_player {
	double px;
	double py;
	double pa;
	double pdx;
	double pdy;
	double planeX;
	double planeY;
	char direction;
}				t_player;

typedef struct s_line
{
	int texX;
	double step;
	double texPos;
	int texY;
	t_player pos;
}				t_line;

typedef struct s_data
{
	char				*file;
	char				*NO; //to optimize
	char				*SO; //to optimize
	char				*WE; //to optimize
	char				*EA; //to optimize
	t_rgb				*F;
	t_rgb				*C;
	char				**map;
	int					nb_of_map_lines;
	void				*mlx;
	void				*win;
	t_cardinal_image	*cardinal_image; //to optimize
	t_main_image		current_img;
	t_player			player;
	t_camera 			camera;

}						t_data;

// PARSING

int						check_ext(char *str, char *ext);
int						read_cub(t_data *data, int fd);
int						get_map(char *line, int fd, t_data *data,
							char *first_line);
int						valid_line(char *line);
void					init_data_map(t_data *data, int line_nb, int line_len,
							char *first_line);
int						store_map(char *first_line, t_data *data);
int						check_values(char **arr);
char					*open_cub(int fd);
int						check_extensions(t_data *data);

// MAP CHECK

int						map_check(t_data *data, int i, int j);

// UTILS

void					print_data(t_data *data);
void					free_data(t_data *data);
void					free_str_arr(char **arr);
void					print_map(t_data *data);
int						print_error(char *str, char *str2);

// EXEC
int						create_trgb(int t, int r, int g, int b);
int						get_img_color(t_cardinal_image img, t_player *pos);
void 					leave_on_error(t_data *data, char *error_statement);
int 					exec(t_data *data);
void 					get_playermap_start_pos(t_data *data);
int						key_func(int key, t_data *data);
int						close_window(t_data *data, char *error, int rtn);
int						load_img(t_data *data, t_cardinal_image *img, char *path);
int 					load_cardinal_images(t_data *data);
int 					init_frame(t_data *data);
void					my_mlx_pixel_put(t_data *data, int x, int y, int color);
int 					draw_sky(t_data *data);
int 					draw_floor(t_data *data);
double 					FixAng(double a);
double 					degToRad(double a);
double 					squareOf(double number);
double 					absoluteOf(double number);
int						close_success(t_data *data);
int 					init_raycaster(t_data *data);
void 					searchHit(int hit, t_camera *camera, t_data *data);
void  					calcSideDist(t_camera *camera, t_data *data);
int 					validMove(t_data *data, int pressed_key);
///
int draw_crosshair(t_data *data);
void render_map(t_data *data);
int draw_stuff(t_data *data, int x, t_camera *camera);
int render_map_all(t_data *data);
int getTexX(t_data *data, t_camera *camera);
int getImgDirection(t_data *data, t_camera *camera);
#endif
