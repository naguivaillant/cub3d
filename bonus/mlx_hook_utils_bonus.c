/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hook_utils_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalhi <nsalhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 14:51:28 by nassm             #+#    #+#             */
/*   Updated: 2024/01/03 17:41:51 by nsalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	key_press_normbis(t_game *g, int keycode)
{
	if (keycode == XK_w)
		g->frames[fr_up] = 1;
	else if (keycode == XK_s)
		g->frames[fr_down] = 1;
	else if (keycode == XK_a)
		g->frames[fr_left] = 1;
	else if (keycode == XK_d)
		g->frames[fr_right] = 1;
}

float	calcul_fb_transdx(int keycode, t_game *g)
{
	float	dx;

	dx = (int)(TRANS_STEP * cos(g->pos.rot * ROT_STEP * PI / 180.0));
	if (keycode == XK_w)
		dx = -dx;
	return (dx);
}

float	calcul_fb_transdy(int keycode, t_game *g)
{
	float	dy;

	dy = (int)(TRANS_STEP * sin(g->pos.rot * ROT_STEP * PI / 180.0));
	if (keycode == XK_w)
		dy = -dy;
	return (dy);
}

float	calcul_side_transdx(int keycode, t_game *g)
{
	float	dx;

	dx = (int)(TRANS_STEP * sin(g->pos.rot * ROT_STEP * PI / 180.0));
	if (keycode == XK_d)
		dx = -dx;
	return (dx);
}

float	calcul_side_transdy(int keycode, t_game *g)
{
	float	dy;

	dy = (int)(TRANS_STEP * -cos(g->pos.rot * ROT_STEP * PI / 180.0));
	if (keycode == XK_d)
		dy = -dy;
	return (dy);
}
