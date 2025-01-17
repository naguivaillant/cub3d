/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precalcul_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalhi <nsalhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 16:57:32 by nassm             #+#    #+#             */
/*   Updated: 2024/01/03 17:42:35 by nsalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	precalcul_init(t_game *g)
{
	int		i;
	int		j;
	float	xp;

	i = -1;
	while (++i < WIDTH)
	{
		xp = WIDTH / 2 - i + 0.5;
		g->ai0[i] = atan(xp / g->dpp) * 180.0 / PI;
		g->cos_ai0[i] = 1 / cos(g->ai0[i] * PI / 180.0);
		g->ai[i] = malloc(sizeof(float) * 360.0 / ROT_STEP);
		g->tan_ai[i] = malloc(sizeof(float) * 360.0 / ROT_STEP);
		g->cos_ai[i] = malloc(sizeof(float) * 360.0 / ROT_STEP);
		g->sin_ai[i] = malloc(sizeof(float) * 360.0 / ROT_STEP);
		if (!g->ai[i] || !g->tan_ai[i] || !g->cos_ai[i] || !g->sin_ai[i])
			end_game(g, 1, "Error at malloc\n");
		j = -1;
		while (++j < 360 / ROT_STEP)
		{
			g->ai[i][j] = angle_convert(j * ROT_STEP + g->ai0[i]);
			g->tan_ai[i][j] = tan(g->ai[i][j] * PI / 180.0);
			g->cos_ai[i][j] = cos(g->ai[i][j] * PI / 180.0);
			g->sin_ai[i][j] = sin(g->ai[i][j] * PI / 180.0);
		}
	}
}

void	precalcul_norm(t_game *g)
{
	g->ai0 = malloc(sizeof(float) * WIDTH);
	g->cos_ai0 = malloc(sizeof(float) * WIDTH);
	g->ai = ft_calloc(sizeof(float *), WIDTH);
	g->tan_ai = ft_calloc(sizeof(float *), WIDTH);
	g->cos_ai = ft_calloc(sizeof(float *), WIDTH);
	g->sin_ai = ft_calloc(sizeof(float *), WIDTH);
	g->a1 = malloc(sizeof(float) * 360.0 / ROT_STEP);
	g->sin_a1 = malloc(sizeof(float) * 360.0 / ROT_STEP);
	g->cos_a1 = malloc(sizeof(float) * 360.0 / ROT_STEP);
	if (!g->ai0 || !g->cos_ai0 || !g->ai || !g->tan_ai || !g->cos_ai
		|| !g->sin_ai || !g->a1 || !g->sin_a1 || !g->cos_a1)
		end_game(g, 1, "Error at malloc\n");
}

int	precalcul(t_game *g)
{
	int		j;

	precalcul_norm(g);
	precalcul_init(g);
	j = -1;
	while (++j < 360 / ROT_STEP)
	{
		g->a1[j] = angle_convert(j * ROT_STEP);
		g->sin_a1[j] = sin(g->a1[j] * PI / 180.0);
		g->cos_a1[j] = cos(g->a1[j] * PI / 180.0);
	}
	g->tol_h = 1.0 / (float) g->map.h / BOX_SIZE;
	g->tol_l = 1.0 / (float) g->map.l / BOX_SIZE;
	return (1);
}
