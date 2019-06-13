/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_input.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crycherd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 17:34:27 by crycherd          #+#    #+#             */
/*   Updated: 2019/06/13 13:11:08 by bomanyte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include "libft.h"
#include "fcntl.h"

void	free_buf(char **buf, int i)
{
	if (buf)
	{
		while (i >= 0)
		{
			free(buf[i]);
			i--;
		}
		free(buf);
	}
}

static char		**fill_buf(int fd)
{
	int		i;
	int		check;
	char	*line;
	char	**buf;

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

static int		check_end(fd)
{
	char	*line;
	int		check;

	if ((check = get_next_line(fd, &line)) && (ft_strlen(line) > 0))
	{
		free(line);
		return(2);
	}
	if (check == 1)
		free(line);
	return (check);
}

t_map	*ft_input(char *file_name)
{
	int		check;
	char	**buf;
	t_map	*list;
	int		fd;

	list = NULL;
	check = 1;
	fd = open(file_name, O_RDONLY);
	while (check)
	{
		if (!(buf = fill_buf(fd)) || ((check = check_end(fd)) == 2) || !(check_fig(buf)))
		{
			ft_lst_del(&list);
			free_buf(buf, 3);
			return (NULL);
		}
		ft_add_to_end_2lst(&list, ft_new_elem2lst(buf));
		free_buf(buf, 3);
	}
	close(fd);
	return (list);
}
