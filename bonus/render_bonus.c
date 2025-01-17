/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalhi <nsalhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 10:11:22 by nassm             #+#    #+#             */
/*   Updated: 2024/01/03 17:43:08 by nsalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

/*
	The create_trgb function in C takes four unsigned char arguments: 
	t for the transparency byte (alpha),
		r for the red component byte, g for the green component byte,
		and b for the blue component byte. It returns an integer that represents
		the color in the TRGB (Transparency,
		Red, Green, Blue) format.

The function uses bitwise shift (<<) and bitwise OR (|) operations to combine
these components into a 32-bit integer,
	where the bytes are arranged as follows:

	The most significant 8 bits (t << 24) represent the transparency
	(alpha) component.
	The next 8 bits (r << 16) represent the red component.
	The following 8 bits (g << 8) represent the green component.
	The least significant 8 bits (b) represent the blue component.

By combining these values using the bitwise OR operator (|),
	you get an integer that represents the complete color in the TRGB format.
	This is an efficient way to create an integer that represents a color by
	combining its individual components in a specific format.
*/

int	create_trgb(unsigned char t, unsigned char r,
		unsigned char g, unsigned char b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	render_object(t_tex *t, int *bg, int x0, int y0)
{
	int	x;
	int	y;
	int	color;

	x0 -= t->l / 2;
	y0 -= t->h;
	y = -1;
	while (++y < t->h)
	{
		x = -1;
		while (++x < t->l)
		{
			color = *((int *) t->addr + x + y * t->l);
			if (color > 0)
				*((int *) bg + x + x0 + (y + y0) * WIDTH) = color;
		}
	}
}

void	render_backgroud(t_game *g)
{
	int			ix;

	g->pos.ax = -1;
	g->pos.ay = -1;
	g->pos.bx = -1;
	g->pos.by = -1;
	ix = -1;
	while (++ix < WIDTH)
	{
		render_box(g, ix);
	}
}

void	scale_window(t_game *g)
{
	int	x;
	int	y;

	if (SCALE > 1)
	{
		y = HEIGHT * SCALE;
		while (--y >= 0)
		{
			x = WIDTH * SCALE;
			while (--x >= 0)
				*((int *) g->mlx.addr_scale + x + y * WIDTH * SCALE) = \
				*((int *) g->mlx.addr + x / SCALE + y / SCALE * WIDTH);
		}
		mlx_put_image_to_window(g->mlx.mlx, g->mlx.win, g->mlx.img_scale, 0, 0);
	}
	else
		mlx_put_image_to_window(g->mlx.mlx, g->mlx.win, g->mlx.img, 0, 0);
}

int	rendering(t_game *g)
{
	frames(g);
	render_backgroud(g);
	render_object(g->gun_tex, (int *)g->mlx.addr, WIDTH / 2, HEIGHT);
	draw_mini_map(g);
	scale_window(g);
	return (1);
}
