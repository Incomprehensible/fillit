/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_input.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crycherd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 17:34:27 by crycherd          #+#    #+#             */
/*   Updated: 2019/06/10 21:15:21 by crycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include "libft.h"
#include "get_next_line.h"
#include "fcntl.h"
#include "stdio.h"

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
		printf("|%s|\n", buf[i]);
		i++;
	}
	printf("\n");
}

char	**fill_buf(int fd)
{
	int i;
	int check;
	char *line;
	char **buf;

	i = 0;
	buf = (char **)malloc(sizeof(char *) * 4);
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
				printf("|%s|\n", a->figs[i]);
				i++;
			}
			printf("\n");
			a = a->next;
		}
	} 
	else
		printf("error\n");
	return (0);
}
