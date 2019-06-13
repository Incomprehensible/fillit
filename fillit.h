/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crycherd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 17:34:56 by crycherd          #+#    #+#             */
/*   Updated: 2019/06/13 13:59:45 by crycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# include "libft.h"

typedef struct		s_list
{
	char			sym;
	char			**figs;
	int				offset_x;
	int				offset_y;
	char			**t_map;
	struct s_list	*next;
	struct s_list	*previous;
}					t_map;

void				*ft_arrmemdel(void **ap);
void				free_buf(char **buf, int i);
t_map				*ft_input(char *file_name);
void				ft_add_to_end_2lst(t_map **start, t_map *new);
t_map				*ft_new_elem2lst(char **buf);
size_t				ft_lstsize(t_map *begin_lst);
int					check_fig(char **buf);
void				ft_lst_del(t_map **start);
#endif
