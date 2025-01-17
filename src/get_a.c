/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_a.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalhi <nsalhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 09:46:31 by nassm             #+#    #+#             */
/*   Updated: 2023/12/15 15:20:58 by nsalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	get_a_norm(t_game *g, float ai)
{
	int	ax;
	int	ay;

	ax = g->pos.ax;
	ay = g->pos.ay;
	ax = g->pos.apx / BOX_SIZE;
	while ((ax >= 0 && ax < g->map.l) && (ay >= 0 && ay < g->map.h)
		&& ((g->map.v[ay][ax] != b_wall)))
	{
		g->pos.apx += g->pos.dpx;
		g->pos.apy += g->pos.dpy;
		ax = g->pos.apx / BOX_SIZE;
		if (ai > 0.0)
			ay = g->pos.apy / BOX_SIZE - 1;
		else
			ay = g->pos.apy / BOX_SIZE;
	}
	g->pos.ax = ax;
	g->pos.ay = ay;
}

static void	get_a_norm_bis(t_game *g, int ix)
{
	if (g->pos.ax < 0 || g->pos.ax >= g->map.l
		|| g->pos.ay < 0 || g->pos.ay >= g->map.h)
	{
		g->pos.da = INFINI;
		return ;
	}
	else
		g->pos.da = (g->pos.py - g->pos.apy) / g->sin_ai[ix][g->pos.rot];
}

static void	get_a(t_game *g, int ix, float ai)
{
	g->pos.apy = ((int)(g->pos.py / BOX_SIZE)) * BOX_SIZE;
	g->pos.dpy = -BOX_SIZE;
	if (ai <= 0.0)
	{
		g->pos.apy += BOX_SIZE;
		g->pos.dpy = BOX_SIZE;
	}
	g->pos.apx = g->pos.px + (g->pos.py - g->pos.apy)
		* g->cos_ai[ix][g->pos.rot] / g->sin_ai[ix][g->pos.rot];
	g->pos.dpx = BOX_SIZE * g->cos_ai[ix][g->pos.rot]
		/ g->sin_ai[ix][g->pos.rot];
	if (ai < 0)
		g->pos.dpx = -g->pos.dpx;
	if (g->pos.apx < 0 || g->pos.apx >= g->map.pl)
	{
		g->pos.da = INFINI;
		return ;
	}
	g->pos.ay = g->pos.apy / BOX_SIZE;
	if (ai > 0.0)
		g->pos.ay--;
	get_a_norm(g, ai);
	get_a_norm_bis(g, ix);
}

void	get_ab(t_game *g, int ix)
{
	float	ai;

	g->pos.da = 0.0;
	g->pos.db = 0.0;
	ai = g->ai[ix][g->pos.rot];
	if ((-g->tol_l < ai && ai < g->tol_l)
		|| (180.0 - g->tol_l < ai) || ai < -(180.0 - g->tol_l))
	{
		g->pos.da = INFINI;
		get_b(g, ix, ai);
	}
	else if ((90.0 - g->tol_h < ai && ai < 90.0 + g->tol_h)
		|| (-90.0 - g->tol_h < ai && ai < -90.0 + g->tol_h))
	{
		g->pos.db = INFINI;
		get_a(g, ix, ai);
	}
	else
	{
		get_a(g, ix, ai);
		get_b(g, ix, ai);
	}
}
