/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalhi <nsalhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:58:06 by nsalhi            #+#    #+#             */
/*   Updated: 2024/01/03 17:28:20 by nsalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "./libft/libft.h"
# include "minilibx-linux/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <limits.h>
# include <math.h>
# include <sys/stat.h>
# include <sys/types.h>

# define WIDTH 450
# define HEIGHT 250
# define SCALE 4
# define FOV 90
# define BOX_SIZE 64
# define WALL_COLISION 8
# define TRANS_STEP 16
# define ROT_STEP 5
# define TRANS_SPEED 5
# define ROT_SPEED 0
# define GUN_SPEED 2
# define PI 3.141592654
# define INFINI 4294967295.0
# define COLOR_BOLD_SLOW_BLINKING "\033[1;5m"
# define COLOR_BOLD_SLOW_BLINKING_RED "\033[1;5;31m"
# define COLOR_BOLD_SLOW_BLINKING_BLUE "\033[1;5;34m"
# define COLOR_BOLD_SLOW_BLINKING_GREEN "\033[1;5;32m"
# define COLOR_BOLD_SLOW_BLINKING_CYAN "\033[1;5;36m"
# define COLOR_BOLD_GREEN "\033[1;32m"
# define COLOR_BOLD_CYAN "\033[1;36m"
# define COLOR_BOLD_BLUE "\033[1;34m"
# define COLOR_BOLD "\033[1m"
# define COLOR_OFF "\033[m"
# define N_TEX 6
# define N_FRAMES 8
# define MAP_CHAR " \n01NSWEX"

/*
t_no: North walls
t_so: South walls
t_we: West walls
t_ea: East walls
t_fl: Floor
t_cl: Ceiling
*/
enum					e_map
{
	b_wall,
	b_ground,
	b_empty,
};

enum					e_tex
{
	t_no,
	t_so,
	t_we,
	t_ea,
	t_fl,
	t_cl
};
enum					e_frame
{
	fr_up,
	fr_down,
	fr_left,
	fr_right,
	fr_rotl,
	fr_rotr,
	fr_gun
};

/*
Map:
- v: value 0,1
- h: height of map
- l: length of map
*/
typedef struct s_map
{
	enum e_map			**v;
	int					h;
	int					l;
	int					ph;
	int					pl;
	int					perso;
	int					in_map;
}						t_map;

/*
Player position
- x: position x
- y: position y
- px: pixel position x
- py: pixel position y
- alpha: angle de rotation
*/
typedef struct s_pos
{
	int					x;
	int					y;
	float				px;
	float				py;
	int					rot;
	int					ax;
	int					ay;
	int					bx;
	int					by;
	float				dpx;
	float				dpy;
	float				apx;
	float				apy;
	float				bpx;
	float				bpy;
	float				da;
	float				db;
}						t_pos;

/*
mlx:
- bpp: bits par pixel
- ll: line size
- ed: endian
*/
typedef struct s_mlx
{
	void				*mlx;
	void				*win;
	void				*img;
	void				*img_scale;
	int					bpp;
	int					ll;
	int					ed;
	char				*addr;
	char				*addr_scale;
}						t_mlx;

/*
texture, images ...:
- bpp: bits par pixel
- ll: line size
- ed: endian
*/
typedef struct s_tex
{
	int					h;
	int					l;
	int					bpp;
	int					ll;
	int					ed;
	void				*img;
	char				*addr;
}						t_tex;

/*
Equations:
a1 * x + b1 * y = c1
a2 * x + b2 * y = c2
*/
typedef struct s_equa2	t_equa2;

struct					s_equa2
{
	float				det;
	float				a1;
	float				b1;
	float				c1;
	float				a2;
	float				b2;
	float				c2;
	float				x;
	float				y;
	void				(*get_det)(t_equa2 *);
	void				(*get_xy)(t_equa2 *);
};

/*
main:
- dpp : distance to Projection Plan
*/
typedef struct s_game
{
	t_map				map;
	t_pos				pos;
	t_mlx				mlx;
	int					dpp;
	int					frames[N_FRAMES];
	t_tex				tex[N_TEX];
	t_tex				gun[3];
	t_tex				sp_tex[3];
	t_tex				sp_att[3];
	t_tex				sp_hit[5];
	t_tex				*gun_tex;
	unsigned int		shoot;
	int					fl_color;
	int					cl_color;
	char				opened;
	float				*ai0;
	float				*cos_ai0;
	float				**ai;
	float				**tan_ai;
	float				**cos_ai;
	float				**sin_ai;
	float				*cos_a1;
	float				*sin_a1;
	float				*a1;
	t_equa2				eq;
	float				tol_h;
	float				tol_l;
	int					count_text;
	int					f;
	int					c;
}						t_game;

typedef struct s_render
{
	int					xh;
	int					yh;
	int					tx;
	int					ty;
	int					i;
	int					ix;
	float				xph;
	float				yph;
	float				dh;
	float				d;
	float				h;
	float				p;
	float				d0;
	float				start_x;
	float				start_y;
	float				end_x;
	float				end_y;
	t_tex				*tex;
}						t_render;

////////////// map.c ////////////////

void					finish(char *s, int fd, t_game *g);
int						get_map(t_game *g, char *fn);

///////////// texture.c /////////////

int						get_color(char *s);
int						get_textures(t_game *g, char *fn);

////////////// map_bis.c ////////////

int						check_map(char *s);

//////////// check.c ///////////////

void					check_wall(t_game *g);

////////// mlx_hook_utils.c ////////////

void					key_press_normbis(t_game *g, int keycode);
float					calcul_fb_transdx(int keycode, t_game *g);
float					calcul_fb_transdy(int keycode, t_game *g);
float					calcul_side_transdx(int keycode, t_game *g);
float					calcul_side_transdy(int keycode, t_game *g);

/////////// map_utils.c ////////////

void					free_map(t_map *m);

//////////// end_game.c //////////

void					free_array(float **a, int size);
int						end_game(t_game *g, int exit_code, char *s);

////////////// render.c ///////////////

int						rendering(t_game *g);
void					render_object(t_tex *t, int *bg, int x0, int y0);
void					render_backgroud(t_game *g);
void					scale_window(t_game *g);
int						create_trgb(unsigned char t, unsigned char r,
							unsigned char g, unsigned char b);
float					render_box(t_game *g, int ix);

/////////// mini_map.c ///////////////

void					draw_mini_map(t_game *g);

////////// angle_convert.c //////////

float					angle_convert(double a);

//////////// mlx_hook.c ////////////

int						key_press(int keycode, t_game *g);
int						key_release(int keycode, t_game *g);

//////////// mlx_mouse_hook.c ///////////
int						mouse_hook(int button, int x, int y, t_game *g);

//////////// get_b.c ///////////////////

void					get_b(t_game *g, int ix, float ai);

///////// get_a.c //////////////
void					get_ab(t_game *g, int ix);

///////////// frames.c ////////////
void					frames(t_game *g);

int						end_game(t_game *g, int exit_code, char *s);
void					init(t_game *g);
int						precalcul(t_game *g);
void					get_pos_norm(int i, int j, char c, t_game *g);
void					init_map_size(t_game *g);
void					free_map(t_map *m);
void					order(t_game *g);
int						get_texture2(t_game *g, char **ss, char *s);
void					for_check_map(t_game *g, char *fn);

/////////////// utils.c ////////////////////

int						astr_len(char **ss);
int						return_error(char *s, char **ss);
int						game_text_normbis(t_game *g, char **ss);
int						get_texture_normbis(char **ss, t_game *g);

int						g_t(t_game *g, t_tex *t, char *path);

bool					check_intmax(char *s);

int						check_fc(char **ss, int i);

#endif