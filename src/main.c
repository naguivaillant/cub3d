/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalhi <nsalhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 11:19:55 by nassm             #+#    #+#             */
/*   Updated: 2024/01/02 17:06:04 by nsalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	main_norm(t_game *g)
{
	if (!g->mlx.mlx || !g->mlx.win)
		end_game(g, EXIT_FAILURE, "Error mlx\n");
	g->mlx.img = mlx_new_image(g->mlx.mlx, WIDTH, HEIGHT);
	g->mlx.img_scale = mlx_new_image(g->mlx.mlx, WIDTH * SCALE, HEIGHT * SCALE);
	g->mlx.addr = mlx_get_data_addr(g->mlx.img,
			&g->mlx.bpp, &g->mlx.ll, &g->mlx.ed);
	g->mlx.addr_scale = mlx_get_data_addr(g->mlx.img_scale,
			&g->mlx.bpp, &g->mlx.ll, &g->mlx.ed);
}

int	main(int ac, char **av)
{
	t_game	game;

	if (ac < 2 || ac > 2)
		return (0);
	init(&game);
	if (!get_map(&game, av[1]) || !precalcul(&game))
		end_game(&game, EXIT_FAILURE, "Error map or memories\n");
	game.mlx.mlx = mlx_init();
	if (game.mlx.mlx == NULL)
		end_game(&game, EXIT_FAILURE, "Error env\n");
	game.mlx.win = mlx_new_window(game.mlx.mlx, WIDTH * SCALE,
			HEIGHT * SCALE, "Cub3D");
	main_norm(&game);
	if (!get_textures(&game, av[1]) || game.count_text != 4
		|| game.fl_color == -1 || game.cl_color == -1)
		end_game(&game, EXIT_FAILURE, "Error textures load\n");
	mlx_mouse_hook(game.mlx.win, mouse_hook, &game);
	mlx_hook(game.mlx.win, 2, KeyPressMask, &key_press, &game);
	mlx_hook(game.mlx.win, 3, KeyReleaseMask, &key_release, &game);
	mlx_hook(game.mlx.win, ClientMessage, LeaveWindowMask, &end_game, &game);
	mlx_loop_hook(game.mlx.mlx, &rendering, &game);
	mlx_loop(game.mlx.mlx);
}
