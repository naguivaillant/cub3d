/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalhi <nsalhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 14:44:19 by nassm             #+#    #+#             */
/*   Updated: 2024/01/03 17:17:53 by nsalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	astr_len(char **ss)
{
	int	n;

	if (!ss)
		return (0);
	n = 0;
	while (ss[n++])
		;
	return (n);
}

int	return_error(char *s, char **ss)
{
	int	i;

	i = 0;
	if (ss != NULL)
	{
		while (ss[i])
		{
			free(ss[i]);
			i++;
		}
		free(ss);
	}
	if (s)
		free(s);
	return (0);
}

int	game_text_normbis(t_game *g, char **ss)
{
	if (ft_strncmp("NO", ss[0], 2) == 0)
	{
		if (ft_strlen(ss[0]) != 2)
			return (0);
		g->count_text++;
		if (!g_t(g, &g->tex[t_no], ss[1]))
			return (0);
	}
	if (ft_strncmp("SO", ss[0], 2) == 0)
	{
		if (ft_strlen(ss[0]) != 2)
			return (0);
		g->count_text++;
		if (!g_t(g, &g->tex[t_so], ss[1]))
			return (0);
	}
	return (1);
}

int	get_texture_normbis(char **ss, t_game *g)
{
	if (ss[0])
	{
		if (ft_strncmp("F", ss[0], 1) == 0)
		{
			g->f++;
			if (check_fc(ss, 1) == 0 || g->f > 1)
				return (0);
		}
		if (ft_strncmp("C", ss[0], 1) == 0)
		{
			g->c++;
			if (check_fc(ss, 1) == 0 || g->c > 1)
				return (0);
		}
	}
	return (1);
}

bool	check_intmax(char *s)
{
	int				len;
	long long int	nb;

	len = ft_strlen(s);
	if (len > 3)
		return (false);
	nb = ft_atol(s);
	if (nb > 255)
		return (false);
	return (true);
}
