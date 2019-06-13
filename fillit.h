/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crycherd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 17:34:56 by crycherd          #+#    #+#             */
/*   Updated: 2019/06/13 15:38:32 by crycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# include "libft.h"

typedef struct		s_map
{
	char			sym;
	char			**figs;
	int				offset_x;
	int				offset_y;
	char			**map;
	struct s_map	*next;
	struct s_map	*previous;
}					t_map;

void				*ft_arrmemdel(void **ap);
int					ft_count_type(t_map *map);
int					ft_check_type(t_map *map, int x, int y, int fig);
int					ft_get_type1(t_map *map);
int					ft_get_type2(t_map *map);
int					fillit(t_map *map, int num);
void				ft_set(t_map *map, int x, int y);
void				ft_updtxy(t_map *map, int num);
int					subst(t_map *map, int num, int flag);
int					ft_check_offset(t_map *map, int num, int flag);
int					ft_remove(t_map *alst);
int					find_x(char **fig, int num);
int					find_y(char **fig, int num);
void				ft_getmap(int size, t_map *lst);
void				ft_check_map(t_map *map, int num);
int					ft_sqrt(int nb);
void				ft_lstdel_one(t_map **alst);
int					ft_printlst(t_map *valid);
char				**ft_arrcopy(char **arr);
void				*ft_arrmemdel(void **ap);
void				free_buf(char **buf, int i);
t_map				*ft_input(char *file_name);
void				ft_add_to_end_2lst(t_map **start, t_map *new);
t_map				*ft_new_elem2lst(char **buf);
size_t				ft_lstsize(t_map *begin_lst);
int					check_fig(char **buf);
void				ft_lst_del(t_map **start);
#endif
