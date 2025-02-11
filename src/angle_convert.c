/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angle_convert.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalhi <nsalhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 17:13:25 by nassm             #+#    #+#             */
/*   Updated: 2023/12/15 15:19:38 by nsalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

float	angle_convert(double a)
{
	while (a > 180.0 || a <= -180.0)
	{
		if (a > 180.0)
			a -= 360.0;
		if (a <= -180.0)
			a += 360.0;
	}
	return (a);
}
