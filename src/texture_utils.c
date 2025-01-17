/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalhi <nsalhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 19:06:25 by nassm             #+#    #+#             */
/*   Updated: 2024/01/08 12:25:38 by nsalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/cub3d.h"

int	g_t(t_game *g, t_tex *t, char *path)
{
	if (t->img)
		return (0);
	t->img = mlx_xpm_file_to_image(g->mlx.mlx, path, &t->l, &t->h);
	if (!t->img)
		return (0);
	t->addr = mlx_get_data_addr(t->img, &t->bpp, &t->ll, &t->ed);
	return (1);
}

int	suite_g_t2(t_game *g, char **ss)
{
	if (!ft_strncmp("FL", ss[0], 3))
	{
		if (!g_t(g, &g->tex[t_fl], ss[1]))
			return (return_error(NULL, ss));
		g->fl_color = 0;
	}
	if (!ft_strncmp("CL", ss[0], 3))
	{
		if (!g_t(g, &g->tex[t_cl], ss[1]))
			return (return_error(NULL, ss));
		g->cl_color = 0;
	}
	return (1);
}

int	game_text_norm(t_game *g, char **ss, char *s)
{
	int	len;

	len = ft_str_arr_len(ss);
	if (len > 2)
		return (return_error(NULL, ss));
	if (!game_text_normbis(g, ss))
		return (return_error(NULL, ss));
	if (ft_strncmp("WE", ss[0], 2) == 0)
	{
		if (ft_strlen(ss[0]) != 2)
			return (return_error(s, ss));
		g->count_text++;
		if (!g_t(g, &g->tex[t_we], ss[1]))
			return (return_error(NULL, ss));
	}
	if (ft_strncmp("EA", ss[0], 2) == 0)
	{
		if (ft_strlen(ss[0]) != 2)
			return (return_error(s, ss));
		g->count_text++;
		if (!g_t(g, &g->tex[t_ea], ss[1]))
			return (return_error(NULL, ss));
	}
	return (1);
}

int	get_texture2(t_game *g, char **ss, char *s)
{
	if (!game_text_norm(g, ss, s))
		return (0);
	if (!suite_g_t2(g, ss))
		return (0);
	if (!ft_strncmp("F", ss[0], 2))
	{
		g->fl_color = get_color(ss[1]);
		if (!g->fl_color)
			return (return_error(NULL, ss));
	}
	else if (!ft_strncmp("C", ss[0], 2))
	{
		g->cl_color = get_color(ss[1]);
		if (!g->cl_color)
			return (return_error(NULL, ss));
	}
	return (1);
}

void	order(t_game *g)
{
	g_t(g, &g->gun[0], "./guns/gun1a.xpm");
	g_t(g, &g->gun[1], "./guns/gun1b.xpm");
	g_t(g, &g->gun[2], "./guns/gun1c.xpm");
}
