/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hook_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalhi <nsalhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 14:42:44 by nassm             #+#    #+#             */
/*   Updated: 2024/01/03 17:41:17 by nsalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	key_press_norm(t_game *g, t_pos *p, int keycode)
{
	if (((keycode == XK_w && !g->frames[fr_up])
			|| (keycode == XK_s && !g->frames[fr_down])
			|| (keycode == XK_a && !g->frames[fr_left])
			|| (keycode == XK_d && !g->frames[fr_right]))
		&& (p->x > 0 && p->y > 0 && p->x < g->map.l
			&& p->y < g->map.h && g->map.v[p->y][p->x] == b_ground
		&& g->map.v[p->y][(int)((g->pos.px - p->px + WALL_COLISION)
		/ BOX_SIZE)] == b_ground
		&& g->map.v[p->y][(int)((g->pos.px - p->px - WALL_COLISION)
		/ BOX_SIZE)] == b_ground
		&& g->map.v[(int)((g->pos.py + p->py + WALL_COLISION)
		/ BOX_SIZE)][p->x] == b_ground
		&& g->map.v[(int)((g->pos.py + p->py - WALL_COLISION)
		/ BOX_SIZE)][p->x] == b_ground))
	{
		g->pos.px -= p->px;
		g->pos.py += p->py;
		g->pos.x = p->x;
		g->pos.y = p->y;
		key_press_normbis(g, keycode);
	}
}

void	key_press_rot(t_game *g, int keycode)
{
	if (keycode == XK_Right || keycode == XK_Left)
	{
		if ((keycode == XK_Right && !g->frames[fr_rotr])
			|| (keycode == XK_Left && !g->frames[fr_rotl]))
		{
			if (keycode == XK_Right)
				g->pos.rot--;
			else
				g->pos.rot++;
			if (g->pos.rot < 0)
				g->pos.rot += 360 / ROT_STEP;
			else if (g->pos.rot >= 360 / ROT_STEP)
				g->pos.rot = 0;
			if (keycode == XK_Right)
				g->frames[fr_rotr] = 1;
			else
				g->frames[fr_rotl] = 1;
		}
	}
}

int	key_press(int keycode, t_game *g)
{
	t_pos	p;

	if (keycode == XK_w || keycode == XK_s
		|| keycode == XK_a || keycode == XK_d)
	{
		if (keycode == XK_w || keycode == XK_s)
		{
			p.px = calcul_fb_transdx(keycode, g);
			p.py = calcul_fb_transdy(keycode, g);
		}
		else
		{
			p.px = calcul_side_transdx(keycode, g);
			p.py = calcul_side_transdy(keycode, g);
		}
		p.x = (int)((g->pos.px - p.px) / BOX_SIZE);
		p.y = (int)((g->pos.py + p.py) / BOX_SIZE);
		key_press_norm(g, &p, keycode);
	}
	key_press_rot(g, keycode);
	return (1);
}

int	key_release(int keycode, t_game *g)
{
	if (keycode == XK_q || keycode == XK_Escape)
	{
		printf("end game\n");
		end_game(g, 0, 0);
	}
	return (1);
}

int	mouse_hook(int button, int x, int y, t_game *g)
{
	float	alpha;

	(void)y;
	if (button == 1)
	{
		alpha = atan(((float) x / SCALE - WIDTH / 2) / g->dpp) * 180.0 / PI;
		g->pos.rot -= (int) alpha / ROT_STEP;
		if (g->pos.rot < 0)
			g->pos.rot += 360 / ROT_STEP;
		else if (g->pos.rot >= 360 / ROT_STEP)
			g->pos.rot -= 360 / ROT_STEP;
	}
	return (1);
}
