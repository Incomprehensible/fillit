/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_twolist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crycherd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 19:05:59 by crycherd          #+#    #+#             */
/*   Updated: 2019/06/13 14:03:40 by crycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

size_t	ft_lstsize(t_map *begin_lst)
{
	size_t i;

	i = 0;
	while (begin_lst)
	{
		begin_lst->sym += i;
		begin_lst = begin_lst->next;
		i++;
	}
	return (i);
}

void	ft_lst_del(t_map **start)
{
	t_map *del;

	if (*start)
	{
		del = *start;
		if (del)
		{
			ft_lst_del(&(del->next));
			free_buf(del->figs, 3);
			free(del);
		}
		*start = NULL;
	}
}

void	ft_add_to_end_2lst(t_map **start, t_map *new)
{
	t_map *list;

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

t_map	*ft_new_elem2lst(char **buf)
{
	t_map	*new;
	int		i;

	if ((new = (t_map *)malloc(sizeof(t_map))))
	{
		new->sym = 'A';
		new->offset_x = 0;
		new->offset_y = 0;
		new->next = NULL;
		new->previous = NULL;
		new->map = NULL;
		i = -1;
		if ((new->figs = (char **)malloc(sizeof(char *) * 4)))
		{
			while (++i < 4)
			{
				if (!(new->figs[i] = ft_strdup(buf[i])))
				{
					free_buf(new->figs, i);
					return (NULL);
				}
			}
		}
	}
	return (new);
}
