/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_validity.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crycherd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 16:10:02 by crycherd          #+#    #+#             */
/*   Updated: 2019/06/11 20:21:53 by crycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int	check_buf(char **buf)
{
	int check;
	int num;
	int i;
	int j;

	check = 1;
	num = 0;
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4 && buf[i][j])
		{
			if (buf[i][j] == '#')
				num++;
			if (buf[i][j] != '.' && buf[i][j] != '#')
				check = 0;
			j++;
		}
		if (buf[i][j] != '\0' || num > 4)
			check = 0;
		i++;
	}
	return (check);
}

int	check_neighbor(char **buf, int x, int y)
{
	int result;

	result = 0;
	if (x > 0 && buf[x - 1][y] == '#')
		result++;
	if (y > 0 && buf[x][y - 1] == '#')
		result++;
	if (x < 3 && buf[x + 1][y] == '#')
		result++;
	if (y < 3 && buf[x][y + 1] == '#')
		result++;
	return (result);
}

int	check_fig(char **buf)
{
	int check;
	int neighbors;
	int i;
	int j;

	check = 0;
	if ((check = check_buf(buf)))
	{
		i = 0;
		neighbors = 0;
		while (i < 4)
		{
			j = 0;
			while (j < 4)
			{
				if (buf[i][j] == '#')
					neighbors += check_neighbor(buf, i, j);
				j++;
			}
			i++;
		}
		if (neighbors < 6)
			check = 0;
	}
	return (check);
}
