/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_bis_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalhi <nsalhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 14:51:14 by nassm             #+#    #+#             */
/*   Updated: 2024/01/03 17:35:57 by nsalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

static void	get_position(t_game *g, int i, int j, char c)
{
	if (c == '0')
		g->map.v[j][i] = b_ground;
	else if (c == '1')
		g->map.v[j][i] = b_wall;
	get_pos_norm(i, j, c, g);
}

void	check_line(t_game *g, char *s, int j)
{
	int	i;

	i = 0;
	while (i < g->map.l)
		g->map.v[j][i++] = b_empty;
	i = -1;
	while (s[++i])
	{
		if (s[i] == 'N' || s[i] == 'W' || s[i] == 'E' || s[i] == 'S')
			g->map.perso++;
		get_position(g, i, j, s[i]);
	}
}

void	for_check_map_norm(t_game *g, int *j, char *s)
{
	g->map.in_map = 1;
	g->map.v[++(*j)] = malloc(sizeof(enum e_map) * g->map.l);
	if (!g->map.v[*j])
		end_game(g, 1, "Invalid number of hero\n");
	check_line(g, s, *j);
}

void	for_check_map(t_game *g, char *str)
{
	int		fd;
	int		j;
	char	*s;

	j = -1;
	g->map.in_map = 0;
	fd = open(str, O_RDONLY);
	s = get_next_line(fd, 0);
	while (s)
	{
		if (check_map(s))
		{
			for_check_map_norm(g, &j, s);
		}
		else if (g->map.in_map)
			finish(s, fd, g);
		free(s);
		s = get_next_line(fd, 0);
	}
	close(fd);
	if (g->map.perso > 1 || g->map.perso == 0)
		end_game(g, 1, "Invalid number of hero\n");
}
