/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalhi <nsalhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 14:30:29 by nassm             #+#    #+#             */
/*   Updated: 2024/01/03 17:39:46 by nsalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	draw_player(int yp, int xp, int *addr)
{
	int	i;
	int	j;

	yp -= 3;
	xp -= 5;
	i = 0;
	while (i < 5)
	{
		j = 0;
		while (j < 5)
		{
			addr[yp * WIDTH + (xp + j)] = create_trgb(1, 255, 0, 0);
			j++;
		}
		yp += 1;
		i++;
	}
}

void	wall(int *addr, int p, int k, int count)
{
	int	v;
	int	i;
	int	h;
	int	l;

	l = (((WIDTH / 4) / 9));
	h = (((HEIGHT / 4) / 9));
	i = 1;
	while (i < h)
	{
		v = 1;
		while (v < l)
		{
			if (count == 1)
				addr[(i + (p * h)) * WIDTH + (v + (k * l))] = create_trgb(1,
						0, 255, 255);
			if (count == 0)
				addr[(i + (p * h)) * WIDTH + (v + (k * l))] = create_trgb(1,
						255, 255, 255);
			v++;
		}
		i++;
	}
}

void	draw_palyer_and_wall(t_game *g, int *addr)
{
	int		i;
	int		j;
	int		k;
	int		p;

	i = g->pos.y - 4;
	p = 0;
	while (i <= g->pos.y + 4)
	{
		k = 0;
		j = g->pos.x - 4;
		while (j <= g->pos.x + 4)
		{
			if (i >= 0 && i < g->map.h && j >= 0 && j < g->map.l
				&& g->map.v[i][j] == b_wall)
				wall(addr, p, k, 0);
			k++;
			j++;
		}
		i++;
		p++;
	}
}

void	draw_mini_map(t_game *g)
{
	int	*addr;

	addr = (int *)g->mlx.addr;
	draw_palyer_and_wall(g, addr);
	draw_player((HEIGHT / 4 / 2), (WIDTH / 4 / 2), addr);
}
