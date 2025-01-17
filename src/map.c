/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalhi <nsalhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 11:38:45 by nassm             #+#    #+#             */
/*   Updated: 2024/01/02 17:11:19 by nsalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	finish(char *s, int fd, t_game *g)
{
	free(s);
	close(fd);
	get_next_line(fd, 1);
	end_game(g, 1, "Error: Invalid Map\n");
}

void	get_map_norm(t_game *g, char *str)
{
	init_map_size(g);
	for_check_map(g, str);
	check_wall(g);
}

void	check_extension(char *str, t_game *g)
{
	int	p;

	p = 0;
	while (str[p])
	{
		if (str[p] == '.')
		{
			if (str[p + 1] == 'c' && str[p + 2]
				== 'u' && str[p + 3] == 'b' && str[p + 4] == '\0')
				return ;
			else
				end_game(g, 1, "Invalid .cub\n");
		}
		p++;
	}
}

int	get_map(t_game *g, char *str)
{
	int		fd;
	char	*s;

	fd = open(str, O_RDONLY);
	if (fd == -1)
		return (0);
	check_extension(str, g);
	s = get_next_line(fd, 0);
	while (s)
	{
		if (s[0] != '\n' && check_map(s))
		{
			g->map.h++;
			if ((int) ft_strlen(s) - 1 > g->map.l)
				g->map.l = (int) ft_strlen(s) - 1;
		}
		free(s);
		s = get_next_line(fd, 0);
	}
	close(fd);
	if (g->map.h < 3 || g->map.l < 3)
		end_game(g, 1, "Error: map too small\n");
	get_map_norm(g, str);
	return (1);
}
