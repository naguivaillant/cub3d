/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalhi <nsalhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 19:04:24 by nassm             #+#    #+#             */
/*   Updated: 2024/01/08 15:24:37 by nsalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	get_color(char *s)
{
	int		i;
	int		c[3];
	char	**ss;

	ss = ft_split(s, ',');
	if (ft_str_arr_len(ss) != 3)
	{
		ft_free_str_array(&ss);
		return (-1);
	}
	i = -1;
	while (ss[++i] && i < 4)
	{
		if (!check_intmax(ss[i]))
		{
			ft_free_str_array(&ss);
			return (0);
		}
		c[i] = ft_atol(ss[i]);
		if (c[i] > 255 || c[i] < 0)
			return (ft_free_str_array(&ss), 0);
	}
	ft_free_str_array(&ss);
	return (create_trgb(1, (unsigned int) c[0],
			(unsigned int) c[1], (unsigned int) c[2]));
}

int	get_texture_norm(char *s, t_game *g)
{
	int		i;
	char	**ss;

	i = -1;
	while (s[++i])
		if (s[i] == '	')
			s[i] = ' ';
	s[ft_strlen(s) - 1] = 0;
	ss = ft_split(s, ' ');
	if (get_texture_normbis(ss, g) == 0)
	{
		ft_free_str_array(&ss);
		return (0);
	}
	if (astr_len(ss) > 1 && !get_texture2(g, ss, s))
	{
		return (0);
	}
	ft_free_str_array(&ss);
	return (1);
}

void	end_texture(t_game *g)
{
	if (!g->fl_color && !g->tex[t_fl].img)
		end_game(g, 1, "Error: No floor texture found\n");
	if (!g->cl_color && !g->tex[t_cl].img)
		end_game(g, 1, "Error: No ceiling texture found\n");
}

int	get_textures_error(int fd)
{
	get_next_line(fd, 1);
	close(fd);
	return (0);
}

int	get_textures(t_game *g, char *fn)
{
	int		fd;
	char	*s;
	char	*s0;

	order(g);
	fd = open(fn, O_RDONLY);
	if (fd == -1)
		return (0);
	s = get_next_line(fd, 0);
	while (s)
	{
		s0 = s;
		if (ft_strlen(s) >= 1 && !get_texture_norm(s, g))
		{
			if (s)
				free(s);
			return (get_textures_error(fd));
		}
		free(s0);
		s = get_next_line(fd, 0);
	}
	close(fd);
	end_texture(g);
	return (1);
}
