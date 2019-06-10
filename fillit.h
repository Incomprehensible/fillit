/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crycherd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 17:34:56 by crycherd          #+#    #+#             */
/*   Updated: 2019/06/10 19:39:21 by crycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef FILLIT_H
# define FILLIT_H

typedef struct m_list
{
    char sym;
    char **figs;
    int offset_x;
    int offset_y;
    char **map;
    struct m_list *next;
    struct m_list *previous;
}               map;

void	ft_add_to_end_2lst(map **start, map *new);
map		*ft_new_elem2lst(char **buf);
void	free_buf(char **buf, int i);

#endif
