/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crycherd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 15:23:23 by crycherd          #+#    #+#             */
/*   Updated: 2019/06/11 15:23:56 by crycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "fillit.h"

int		main(int ac, char **av)
{
	map *a;
	int i;
	int size;

	a = ft_input(av[1]);
	size = ft_lstsize(a);
	if (a)
	{
		while (a)
		{
			i = 0;
			ft_putchar(a->sym);
			ft_putstr("\n");
			while (i < 4)
			{
				ft_putstr(a->figs[i]);
				ft_putstr("\n");
				i++;
			}
			ft_putstr("\n");
			a = a->next;
		}
	} 
	else
		ft_putstr("error\n");
	return (0);
}
