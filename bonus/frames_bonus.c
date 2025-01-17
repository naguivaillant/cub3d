/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frames_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalhi <nsalhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:40:49 by nassm             #+#    #+#             */
/*   Updated: 2024/01/03 17:33:09 by nsalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

static void	gun(t_game *g)
{
	if (g->frames[fr_gun] > GUN_SPEED)
		g->frames[fr_gun] = 0;
	if (g->frames[fr_gun] == 1)
		g->gun_tex = &g->gun[1];
	else if (g->frames[fr_gun] == 2)
		g->gun_tex = &g->gun[2];
	else
		g->gun_tex = &g->gun[0];
}

void	frames(t_game *g)
{
	int	i;

	if (g->frames[fr_up] > TRANS_SPEED)
		g->frames[fr_up] = 0;
	if (g->frames[fr_down] > TRANS_SPEED)
		g->frames[fr_down] = 0;
	if (g->frames[fr_left] > TRANS_SPEED)
		g->frames[fr_left] = 0;
	if (g->frames[fr_right] > TRANS_SPEED)
		g->frames[fr_right] = 0;
	if (g->frames[fr_rotr] > ROT_SPEED)
		g->frames[fr_rotr] = 0;
	if (g->frames[fr_rotl] > ROT_SPEED)
		g->frames[fr_rotl] = 0;
	gun(g);
	i = -1;
	while (++i < N_FRAMES)
		if (g->frames[i])
			g->frames[i]++;
}
