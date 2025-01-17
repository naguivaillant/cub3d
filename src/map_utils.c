/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nassm <nassm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 11:56:45 by nassm             #+#    #+#             */
/*   Updated: 2023/12/11 17:51:53 by nassm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	free_map(t_map *m)
{
	int	i;

	if (!m->v)
		return ;
	i = -1;
	while (++i < m->h)
		if (m->v[i])
			free(m->v[i]);
	free(m->v);
}

void	init_map_size(t_game *g)
{
	int	i;

	g->map.ph = g->map.h * BOX_SIZE;
	g->map.pl = g->map.l * BOX_SIZE;
	g->map.v = malloc(sizeof(enum e_map *) * g->map.h);
	if (!g->map.v)
		end_game(g, 1, "Error at mmaloc\n");
	i = -1;
	while (++i < g->map.h)
		g->map.v[i] = 0;
}

void	get_pos_norm(int i, int j, char c, t_game *g)
{
	if (c == ' ')
		g->map.v[j][i] = b_empty;
	else if (ft_strchr("NSWE", c))
	{
		g->map.v[j][i] = b_ground;
		g->pos.x = i;
		g->pos.y = j;
		g->pos.px = i * BOX_SIZE + BOX_SIZE / 2;
		g->pos.py = j * BOX_SIZE + BOX_SIZE / 2;
		if (c == 'N')
			g->pos.rot = 90 / ROT_STEP;
		else if (c == 'S')
			g->pos.rot = 270 / ROT_STEP;
		else if (c == 'W')
			g->pos.rot = 180 / ROT_STEP;
		else if (c == 'E')
			g->pos.rot = 0;
	}
}
