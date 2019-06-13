/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bomanyte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 23:40:14 by bomanyte          #+#    #+#             */
/*   Updated: 2019/06/13 15:34:32 by crycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int		ft_remove(t_map *alst)
{
	t_map *head;
	t_map *valid;

	valid = alst;
	alst = alst->previous;
	while (alst)
	{
		head = alst;
		ft_lstdel_one(&head);
		alst = alst->previous;
	}
	valid->previous = NULL;
	head = NULL;
	return (ft_printlst(valid));
}

void	ft_getmap(int size, t_map *lst)
{
	char	**map;
	int		i;
	int		j;

	map = (char **)malloc(sizeof(char *) * size + 1);
	map[size] = NULL;
	i = 0;
	j = 0;
	while (i < size)
	{
		map[i] = ft_strnew(size);
		while (j < size)
		{
			map[i][j] = '.';
			j++;
		}
		i++;
		j = 0;
	}
	lst->map = map;
}

int		find_x(char **fig, int num)
{
	static int	x;
	int			x1;
	static int	y;
	int			temp;

	x = (num == 0 ? 0 : x);
	y = (num == 0 ? 0 : ++y);
	x1 = (num == 0 ? 0 : x);
	while (fig[x1][y] != '#' && x1 < 4 && num < 5)
	{
		if (fig[x1][y] == '\0')
		{
			x1++;
			y = -1;
		}
		y++;
	}
	temp = x;
	x = x1;
	y = (x1 == 3 ? 0 : y);
	return (num == 0 ? 0 : x1 - temp);
}

int		find_y(char **fig, int num)
{
	static int	y;
	static int	x;
	int			y1;
	int			temp;

	x = (num == 0 ? 0 : x);
	y = (num == 0 ? 0 : y);
	y1 = (num == 0 ? 0 : y + 1);
	while (fig[x][y1] != '#')
	{
		if (fig[x][y1] == '\0')
		{
			x++;
			y1 = -1;
		}
		y1++;
	}
	temp = y;
	y = y1;
	return (num == 0 ? 0 : y1 - temp);
}

void	ft_check_map(t_map *map, int num)
{
	ft_arrmemdel((void **)map->map);
	if (!map->previous)
		ft_getmap(num, map);
	else
		map->map = ft_arrcopy(map->previous->map);
}
