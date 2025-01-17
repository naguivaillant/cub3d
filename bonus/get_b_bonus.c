/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_b_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalhi <nsalhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 09:40:42 by nassm             #+#    #+#             */
/*   Updated: 2024/01/03 17:34:21 by nsalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	get_b_norm_bis(t_game *g, int ix)
{
	if (g->pos.bx < 0 || g->pos.bx >= g->map.l
		|| g->pos.by < 0 || g->pos.by >= g->map.h)
	{
		g->pos.db = INFINI;
		return ;
	}
	else
		g->pos.db = (g->pos.bpx - g->pos.px)
			/ g->cos_ai[ix][g->pos.rot];
}

void	get_b_norm(t_game *g, float ai)
{
	g->pos.bx = g->pos.bpx / BOX_SIZE;
	if (ai <= -90.0 || ai >= 90.0)
		g->pos.bx--;
	while ((g->pos.bx >= 0 && g->pos.bx < g->map.l)
		&& (g->pos.by >= 0 && g->pos.by < g->map.h)
		&& ((g->map.v[g->pos.by][g->pos.bx] != b_wall)))
	{
		g->pos.bpx += g->pos.dpx;
		g->pos.bpy += g->pos.dpy;
		g->pos.by = g->pos.bpy / BOX_SIZE;
		if (ai > -90.0 && ai < 90.0)
			g->pos.bx = g->pos.bpx / BOX_SIZE;
		else
			g->pos.bx = g->pos.bpx / BOX_SIZE - 1;
	}
}

void	get_b(t_game *g, int ix, float ai)
{
	if (ai > -90.0 && ai < 90.0)
	{
		g->pos.bpx = ((int)(g->pos.px / BOX_SIZE)) * BOX_SIZE + BOX_SIZE;
		g->pos.dpx = BOX_SIZE;
	}
	else
	{
		g->pos.bpx = ((int)(g->pos.px / BOX_SIZE)) * BOX_SIZE;
		g->pos.dpx = -BOX_SIZE;
	}
	g->pos.bpy = g->pos.py + (g->pos.px - g->pos.bpx)
		* g->tan_ai[ix][g->pos.rot];
	g->pos.dpy = BOX_SIZE * g->tan_ai[ix][g->pos.rot];
	if (ai * g->pos.dpy > 0)
		g->pos.dpy = -g->pos.dpy;
	if (g->pos.bpy < 0 || g->pos.bpy >= g->map.ph)
	{
		g->pos.db = INFINI;
		return ;
	}
	g->pos.by = g->pos.bpy / BOX_SIZE;
	get_b_norm(g, ai);
	get_b_norm_bis(g, ix);
}
