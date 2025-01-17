/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nassm <nassm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 11:45:47 by nassm             #+#    #+#             */
/*   Updated: 2023/12/11 17:52:21 by nassm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	free_array(float **a, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (a[i])
			free(a[i]);
		i++;
	}
	free(a);
}

void	verif_for_free(t_game *g)
{
	if (g->ai0)
		free(g->ai0);
	if (g->cos_ai0)
		free(g->cos_ai0);
	if (g->ai)
		free_array(g->ai, WIDTH);
	if (g->tan_ai)
		free_array(g->tan_ai, WIDTH);
	if (g->cos_ai)
		free_array(g->cos_ai, WIDTH);
	if (g->sin_ai)
		free_array(g->sin_ai, WIDTH);
	if (g->cos_a1)
		free(g->cos_a1);
	if (g->sin_a1)
		free(g->sin_a1);
	if (g->a1)
		free(g->a1);
}

void	end_game_norm(t_game *g)
{
	int	i;

	i = -1;
	while (++i < 5)
		if (g->sp_hit[i].img)
			mlx_destroy_image(g->mlx.mlx, g->sp_hit[i].img);
	i = -1;
	while (++i < 3)
		if (g->gun[i].img)
			mlx_destroy_image(g->mlx.mlx, g->gun[i].img);
	if (g->mlx.img)
		mlx_destroy_image(g->mlx.mlx, g->mlx.img);
	if (g->mlx.img_scale)
		mlx_destroy_image(g->mlx.mlx, g->mlx.img_scale);
	if (g->mlx.mlx)
	{
		mlx_destroy_window(g->mlx.mlx, g->mlx.win);
		mlx_destroy_display(g->mlx.mlx);
		free(g->mlx.mlx);
	}
}

int	end_game(t_game *g, int exit_code, char *s)
{
	int	i;

	i = -1;
	while (++i < N_TEX)
		if (g->tex[i].img)
			mlx_destroy_image(g->mlx.mlx, g->tex[i].img);
	i = -1;
	while (++i < 3)
		if (g->sp_tex[i].img)
			mlx_destroy_image(g->mlx.mlx, g->sp_tex[i].img);
	i = -1;
	while (++i < 3)
		if (g->sp_att[i].img)
			mlx_destroy_image(g->mlx.mlx, g->sp_att[i].img);
	end_game_norm(g);
	if (g->map.h && g->map.l)
		free_map(&g->map);
	if (s)
		ft_putstr_fd(s, 2);
	verif_for_free(g);
	exit(exit_code);
	return (1);
}
