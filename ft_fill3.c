/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bomanyte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 20:29:35 by bomanyte          #+#    #+#             */
/*   Updated: 2019/06/13 14:27:37 by crycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	ft_set(t_map *map, int x, int y)
{
	if (!map->previous)
	{
		map->offset_x = x;
		map->offset_y = y;
	}
	else
	{
		map->offset_x = 0;
		map->offset_y = 0;
	}
}

void	ft_updtxy(t_map *map, int num)
{
	if (map->offset_y >= num)
	{
		map->offset_x++;
		map->offset_y = 0;
	}
}

int		subst(t_map *map, int num, int flag)
{
	int y;
	int x;

	ft_updtxy(map, num);
	x = map->offset_x;
	y = map->offset_y;
	while (flag++ < 4)
	{
		x += find_x(map->figs, flag - 1);
		y += find_y(map->figs, flag - 1);
		if (x >= num || map->map[x][y] != '.')
		{
			if (x >= num || (x >= num - 1 && y >= num))
			{
				ft_set(map, x, y);
				return ((int)ft_arrmemdel((void **)map->map));
			}
			map->offset_y++;
			ft_check_map(map, num);
			return (subst(map, num, 0));
		}
		map->map[x][y] = map->sym;
	}
	return (++map->offset_y);
}

int		ft_check_offset(t_map *map, int num, int flag)
{
	if (flag == 1)
	{
		if (map->offset_x > num - 1 ||
				(map->offset_x >= num - 1 && map->offset_y >= num - 3))
			return (0);
		return (1);
	}
	else
	{
		if (map->previous && (map->previous->offset_x > num - 1 ||
					(map->previous->offset_x >= num - 1 &&
	map->previous->offset_y >= num - 3)))
		{
			ft_set(map->previous, 0, 0);
			ft_arrmemdel((void **)map->previous->map);
			return (0);
		}
		return (1);
	}
}
