/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 10:28:42 by anda-cun          #+#    #+#             */
/*   Updated: 2024/01/24 18:16:07 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H

# define CUB3D_H

# define GAME_NAME "cub3d"
# define INITIAL_XSIZE 960 // 960
# define INITIAL_YSIZE 540 // 540
# define ERROR -1314
# define PLAYER_SPEED 0.1
# define CONSTANT_DISTANCE 0.5
# define CAMERA_SPEED 1.5
# define INVALID_POSITION -1

# include "../minilibx-linux/mlx.h"
# include "libft.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>

enum					e_FINAL
{
	SUCCESS,
	FAILURE,
};

enum					e_CARDINAL
{
	NORTH,
	SOUTH,
	WEST,
	EAST,
};

enum					e_KEYS
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
	double				camera_x;
	double				ray_dir_x;
	double				ray_dir_y;
	int					map_x;
	int					map_y;
	double				side_dist_x;
	double				side_dist_y;
	double				delta_dist_x;
	double				delta_dist_y;
	double				perp_wall_dist;
	int					step_x;
	int					step_y;
	int					side;
	int					x;
	double				wall_x;
	double				line_height;
}						t_camera;

typedef struct s_rgb
{
	int					red;
	int					green;
	int					blue;
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

typedef struct s_player
{
	double				px;
	double				py;
	double				pa;
	double				pdx;
	double				pdy;
	double				plane_x;
	double				plane_y;
	char				direction;
}						t_player;

typedef struct s_line
{
	int					tex_x;
	double				step;
	double				tex_pos;
	int					tex_y;
	t_player			pos;
}						t_line;

typedef struct s_data
{
	char				*file;
	int					fd;
	t_rgb				*floor;
	t_rgb				*ceiling;
	char				**map;
	int					nb_of_map_lines;
	void				*mlx;
	void				*win;
	t_cardinal_image	*cardinal_image;
	t_main_image		current_img;
	t_player			player;
	t_camera			camera;

}						t_data;

// PARSING

int						parsing(t_data *data);
int						check_ext(char *str, char *ext);
int						read_cub(t_data *data, char *line);
int						get_map(char *line, t_data *data,
							char *first_line);
int						valid_map_line(char *line);
void					init_data_map(t_data *data, int line_nb, int line_len,
							char *first_line);
void						store_map(char *first_line, t_data *data);
int						check_rgb_values(char **arr);
int						check_file(char *str);
void					free_map(char **map);
int						map_check(t_data *data, char **map, int i, int j);
void					free_data(t_data *data);
void					free_str_arr(char **arr);
int						print_error(char *str, char *str2);

// EXEC
int						create_trgb(int t, int r, int g, int b);
int						get_img_color(t_cardinal_image img, t_player *pos);
void					leave_on_error(t_data *data, char *error_statement);
int						exec(t_data *data);
void					get_playermap_start_pos(t_data *data);
int						key_func(int key, t_data *data);
int						close_window(t_data *data, char *error, int rtn);
int						load_img(t_data *data, t_cardinal_image *img,
							char *path);
int						load_cardinal_images(t_data *data);
int						init_frame(t_data *data);
void					my_mlx_pixel_put(t_data *data, int x, int y, int color);
double					fix_ang(double a);
double					deg_to_rad(double a);
double					square_of(double number);
double					absolute_of(double number);
int						close_success(t_data *data);
int						init_raycaster(t_data *data);
void					search_hit(int hit, t_camera *camera, t_data *data);
void					calc_side_dist(t_camera *camera, t_data *data);
int						valid_move(t_data *data, int pressed_key);
///
int						draw_crosshair(t_data *data);
void					render_map(t_data *data);
int						draw_stuff(t_data *data, t_camera *camera);
int						render_map_all(t_data *data);
int						gettex_x(t_data *data, t_camera *camera);
int						get_img_direction(t_data *data, t_camera *camera);
#endif