/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bomanyte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 23:41:27 by bomanyte          #+#    #+#             */
/*   Updated: 2019/06/13 15:35:57 by crycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int		ft_sqrt(int nb)
{
	int i;

	i = 1;
	if (nb <= 0)
		return (0);
	else
	{
		while (i * i < nb)
			i++;
		if (i * i == nb)
			return (i);
		else
			return (i);
	}
}

void	*ft_arrmemdel(void **ap)
{
	unsigned char	**ptr;
	int				i;
	int				j;

	i = 0;
	j = 0;
	ptr = (unsigned char **)ap;
	while (ptr[i])
		i++;
	while (j < i)
	{
		ft_strdel((char **)&(ptr[j]));
		j++;
	}
	free(ap);
	return (NULL);
}

char	**ft_arrcopy(char **arr)
{
	int		i;
	int		j;
	char	**new;

	i = 0;
	j = 0;
	while (arr[i])
		i++;
	new = (char **)malloc(sizeof(new) * (i + 1));
	while (j < i)
	{
		new[j] = ft_strdup(arr[j]);
		j++;
	}
	new[j] = NULL;
	return (new);
}

void	ft_lstdel_one(t_map **alst)
{
	t_map	*head;

	head = *alst;
	if (!alst)
		return ;
	if (head->map)
		ft_arrmemdel((void **)head->map);
	free_buf(head->figs, 3);
	free(head);
	head = NULL;
}

int		ft_printlst(t_map *valid)
{
	int	i;

	i = 0;
	while (valid->map[i])
	{
		ft_putstr(valid->map[i]);
		free(valid->map[i]);
		ft_putchar('\n');
		i++;
	}
	free(valid->map);
	free_buf(valid->figs, 3);
	free(valid);
	return (1);
}
