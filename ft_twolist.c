/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_twolist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crycherd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 19:05:59 by crycherd          #+#    #+#             */
/*   Updated: 2019/06/10 19:49:46 by crycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include "libft.h"

void	ft_add_to_end_2lst(map **start, map *new)
{
	map *list;

	if (*start)
	{
		list = *start;
		while (list->next)
			list = list->next;
		list->next = new;
		new->previous = list;
	}
	else
		*start = new;
}

map		*ft_new_elem2lst(char **buf)
{
	map *new;
	int i;

	if ((new = (map *)malloc(sizeof(map))))
	{
		new->sym = 'A';
		new->offset_x = 0;
		new->offset_y = 0;
		new->next = NULL;
		new->previous = NULL;
		new->map = NULL;
		i = 0;
		if ((new->figs = (char **)malloc(sizeof(char *) * 4)))
		{
			while(i < 4)
			{
				if (!(new->figs[i] = ft_strdup(buf[i])))
				{
					free_buf(new->figs, i);
					return (NULL);
				}
				i++;
			}
		}
	}
	return (new);
}
