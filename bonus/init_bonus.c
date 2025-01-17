/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalhi <nsalhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 11:21:29 by nassm             #+#    #+#             */
/*   Updated: 2024/01/03 17:35:00 by nsalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	get_det(t_equa2 *e)
{
	e->det = e->a1 * e->b2 - e->b1 * e->a2;
}

void	get_xy(t_equa2 *e)
{
	e->get_det(e);
	e->x = (e->b2 * e->c1 - e->b1 * e->c2) / e->det;
	e->y = (e->c2 * e->a1 - e->c1 * e->a2) / e->det;
}

void	init_norm(t_game *g)
{
	g->mlx.mlx = 0;
	g->mlx.img = 0;
	g->mlx.img_scale = 0;
	g->ai = 0;
	g->ai0 = 0;
	g->cos_ai0 = 0;
	g->tan_ai = 0;
	g->cos_ai = 0;
	g->sin_ai = 0;
	g->cos_a1 = 0;
	g->sin_a1 = 0;
	g->a1 = 0;
	g->fl_color = 0;
	g->cl_color = 0;
	g->opened = 0;
	g->gun_tex = &g->gun[0];
	g->eq.get_det = get_det;
	g->eq.get_xy = get_xy;
	g->count_text = 0;
}

void	init_mapandhero(t_game *g)
{
	g->map.v = 0;
	g->map.h = 0;
	g->map.l = 0;
	g->map.ph = 0;
	g->map.pl = 0;
	g->map.perso = 0;
	g->pos.x = 0;
	g->pos.y = 0;
	g->pos.rot = 0;
	g->f = 0;
	g->c = 0;
}

void	init(t_game *g)
{
	int	i;

	init_mapandhero(g);
	g->dpp = (int) WIDTH / 2 / tan(PI / 180 * FOV / 2);
	i = -1;
	while (++i < N_TEX)
		g->tex[i].img = 0;
	i = -1;
	while (++i < N_FRAMES)
		g->frames[i] = 0;
	i = -1;
	while (++i < 3)
		g->gun[i].img = 0;
	i = -1;
	while (++i < 3)
		g->sp_tex[i].img = 0;
	i = -1;
	while (++i < 3)
		g->sp_att[i].img = 0;
	i = -1;
	while (++i < 5)
		g->sp_hit[i].img = 0;
	init_norm(g);
}
