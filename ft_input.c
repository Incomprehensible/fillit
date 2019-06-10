/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_input.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crycherd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 17:34:27 by crycherd          #+#    #+#             */
/*   Updated: 2019/06/10 22:06:05 by crycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include "libft.h"
#include "get_next_line.h"
#include "fcntl.h"

void	free_buf(char **buf, int i)
{
	while (i >= 0)
	{
		free(buf[i]);
		i--;
	}
	free(buf);
}

void	check_buf(char **buf)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		ft_putstr("|");
		ft_putstr(buf[i]);
		ft_putstr("|");
		ft_putstr("\n");
		i++;
	}
	ft_putstr("\n");
}

char	**fill_buf(int fd)
{
	int i;
	int check;
	char *line;
	char **buf;

	i = 0;
	if ((buf = (char **)malloc(sizeof(char *) * 4)))
	{
		while (i < 4 && (check = get_next_line(fd, &line)))
		{
			buf[i] = ft_strdup(line);
			free(line);
			i++;
		}
		if (check == 0)
		{
			free_buf(buf, i - 1);
			return (NULL);
		}
	}
	return (buf);
}

int		check_end(fd)
{
	char *line;
	int check;

	if ((check = get_next_line(fd, &line)) && (ft_strlen(line) > 0))
	{
		free(line);
		return(2);
	}
	return (check);
}

map		*ft_input(char *file_name)
{
	int check;
	char **buf;
	map *list;
	int fd;

	list = NULL;
	check = 1;
	fd = open(file_name, O_RDONLY);
	while (check)
	{
		if (!(buf = fill_buf(fd)))
			return (NULL);
		ft_add_to_end_2lst(&list, ft_new_elem2lst(buf));
		free_buf(buf, 3);
		if ((check = check_end(fd)) == 2)
			return (NULL);
	}
	close(fd);
	return (list);
}

int		main(int ac, char **av)
{
	map *a;
	int i;

	a = ft_input(av[1]);
	if (a)
	{
		while (a)
		{
			i = 0;
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
