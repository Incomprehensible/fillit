/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bomanyte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 23:34:38 by bomanyte          #+#    #+#             */
/*   Updated: 2019/06/13 15:30:42 by crycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int		fillit(t_map *map, int num)
{
	while (map)
	{
		if (subst(map, num, 0) != 0)
		{
			if (map->next && map->next->figs)
				map = map->next;
			else
				return (ft_remove(map));
			map->map = ft_arrcopy(map->previous->map);
		}
		else
		{
			if (!map->previous && !ft_check_offset(map, num, 1))
				return (0);
			if (!ft_check_offset(map, num, 2))
				map = map->previous->previous;
			else
				map = map->previous;
			ft_check_map(map, num);
		}
	}
	return (1);
}

int		ft_check_type(t_map *map, int x, int y, int fig)
{
	int i;

	i = 0;
	while (!fig && y != 4 && map->figs[x][y] == '#')
	{
		y++;
		i++;
		if (i == 3)
			return (1);
	}
	while (fig && x != 4 && map->figs[x][y] == '#')
	{
		x++;
		i++;
		if (i == 3)
			return (1);
	}
	return (0);
}

int		ft_get_type1(t_map *map)
{
	int x;
	int y;
	int type;

	type = 0;
	while (map)
	{
		y = 0;
		x = 0;
		while (map->figs[x][y] != '#')
		{
			while (y != 4 && map->figs[x][y] != '#')
				y++;
			if (y == 4)
			{
				x++;
				y = 0;
			}
		}
		type += ft_check_type(map, x, ++y, 0);
		map = map->next;
	}
	return (type);
}

int		ft_get_type2(t_map *map)
{
	int x;
	int y;
	int type;

	type = 0;
	while (map)
	{
		x = 0;
		y = 0;
		while (map->figs[x][y] != '#')
		{
			while (y != 4 && map->figs[x][y] != '#')
				y++;
			if (y == 4)
			{
				x++;
				y = 0;
			}
		}
		type += ft_check_type(map, ++x, y, 1);
		map = map->next;
	}
	return (type);
}

int		ft_count_type(t_map *map)
{
	int type_1;
	int type_2;

	type_1 = ft_get_type1(map);
	type_2 = ft_get_type2(map);
	if (type_2 > type_1 && type_2 <= 8)
		return (type_2);
	else if (type_1 > type_2 && type_1 <= 8)
		return (type_1);
	if (type_1 > type_2 && type_1 < 16 && type_1 > 8)
		return (8);
	else if (type_2 > type_1 && type_2 < 16 && type_2 > 8)
		return (8);
	return (0);
}
