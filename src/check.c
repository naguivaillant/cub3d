/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nassm <nassm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 14:52:41 by nassm             #+#    #+#             */
/*   Updated: 2023/12/20 10:50:59 by nassm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	check_map(char *s)
{
	char	*s0;

	s0 = s;
	if (s[0] == '\n')
		return (0);
	while (*s0 && ft_strchr(" 	\n", *s0))
		s0++;
	if (!*s0)
		return (0);
	while (*s)
		if (!ft_strchr(MAP_CHAR, *(s++)))
			return (0);
	return (1);
}

void	check(int x, t_game *g)
{
	if (g->map.v[0][x] == b_ground || g->map.v[g->map.h - 1][x] == b_ground)
		end_game(g, 1, "Error: Invalid map Ground Wall\n");
}

int	check_wall_norm(t_game *g, int w, int x)
{
	if (w == 0 && g->map.v[w][x] == b_ground)
		return (0);
	else if ((x == 0 || x == g->map.l - 1) && g->map.v[w][x] == b_ground)
		return (0);
	else if (g->map.v[w][x] == b_ground && ((g->map.v[w][x + 1]
				&& g->map.v[w][x + 1] == b_empty) || (g->map.v[w][x - 1]
				&& g->map.v[w][x - 1] == b_empty) || (g->map.v[w + 1][x]
				&& g->map.v[w + 1][x] == b_empty)
				|| (g->map.v[w - 1][x] && g->map.v[w - 1][x] == b_empty)))
		return (0);
	return (1);
}

void	check_wall(t_game *g)
{
	int	w;
	int	x;

	w = 0;
	while (w < g->map.h)
	{
		x = 0;
		while (x < g->map.l)
		{
			check(x, g);
			if (!check_wall_norm(g, w, x))
				end_game(g, 1, "Error: Invalid map\n");
			x++;
		}
		if (g->map.v[w][g->map.l - 1] == b_ground || g->map.v[w][0] == b_ground)
			end_game(g, 1, "Error: Invalid map\n");
		w++;
	}
}
