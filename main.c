/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bomanyte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 23:37:12 by bomanyte          #+#    #+#             */
/*   Updated: 2019/06/13 13:07:51 by bomanyte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include "libft.h"

int		main(int argc, char **argv)
{
	int		ret;
	t_map	*field;
	int		rows;

	if (argc == 2)
	{
		if ((field = ft_input(argv[1])))
		{
			rows = ft_sqrt(ft_lstsize(field) * 4);
			ret = ft_count_type(field);
			if (rows < ret)
				rows = ret;
			ft_getmap(rows, field);
			while (fillit(field, rows) == 0)
			{
				ft_set(field, 0, 0);
				ft_getmap(++rows, field);
			}
		}
		else
			ft_putstr("error\n");
	}
	else
		ft_putstr("usage: ./fillit target_file\n");
	return (0);
}
