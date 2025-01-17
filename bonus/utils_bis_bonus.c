/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bis_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalhi <nsalhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 17:46:35 by nsalhi            #+#    #+#             */
/*   Updated: 2024/01/03 17:59:44 by nsalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

int	check_fc(char **ss, int i)
{
	int	x;

	x = 0;
	if (ss[i])
	{
		while (ss[i][x])
		{			
			if (!ft_isdigit(ss[i][x]) && ss[i][x] != ',')
				return (0);
			x++;
		}
	}
	return (1);
}
