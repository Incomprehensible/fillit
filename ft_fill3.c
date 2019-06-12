/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bomanyte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 20:29:35 by bomanyte          #+#    #+#             */
/*   Updated: 2019/06/12 23:19:13 by crycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include "libft.h"

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

char **ft_arrcopy(char **arr)
{
    int i;
    int j;
    char **new;

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
    map *head;

    head = *alst;
    if (!alst)
        return ;
    if (head->map)
		ft_arrmemdel((void **)head->map);
	free_buf(head->figs, 3);
    free(head);
    head = NULL;
}

int    ft_printlst(t_map *valid) {
    int i;

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

int    ft_remove(t_map *alst)
{
    map *head;
    map *valid;

    valid = alst;
    alst = alst->previous;
    while (alst)
    {
        head = alst;
        ft_lstdel_one(&head);
        alst = alst->previous;
    }
    valid->previous = NULL;
    head = NULL;
    return (ft_printlst(valid));
}

void  ft_getmap(int size, map *lst) {
    char **map;
    int i;
    int j;

    map = (char **) malloc(sizeof(map) * size + 1);
    map[size] = NULL;
    i = 0;
    j = 0;
    while (i < size) {
        map[i] = ft_strnew(size);
        while (j < size) {
            map[i][j] = '.';
            j++;
        }
        i++;
        j = 0;
    }
    lst->map = map;
}

int find_x(char **fig, int num)
{
    static int x;
    int x1;
    static int y;
    int temp;

    x = (num == 0 ? 0 : x);
    y = (num == 0 ? 0 : ++y);
    x1 = (num == 0 ? 0 : x);
    while (fig[x1][y] != '#' && x1 < 4 && num < 5)
    {
        if (fig[x1][y] == '\0')
        {
            x1++;
            y = -1;
        }
        y++;
    }
    temp = x;
    x = x1;
    y = (x1 == 3 ? 0 : y);
    return (num == 0 ? 0 : x1 - temp);
}

int find_y(char **fig, int num)
{
    static int y;
    static int x;
    int y1;
    int temp;

    x = (num == 0 ? 0 : x);
    y = (num == 0 ? 0 : y);
    y1 = (num == 0 ? 0 : y + 1);
    while (fig[x][y1] != '#')
    {
        if (fig[x][y1] == '\0')
        {
            x++;
            y1 = -1;
        }
        y1++;
    }
    temp = y;
    y = y1;
    return (num == 0 ? 0 : y1 - temp);
}

void ft_check_map(t_map *map, int num)
{
	ft_arrmemdel((void **)map->map);
	if (!map->previous)
		ft_getmap(num, map);
	else
		map->map = ft_arrcopy(map->previous->map);
}

void    ft_set(t_map *map, int x, int y)
{
    if (!map->previous) {
        map->offset_x = x;
        map->offset_y = y;
    }
    else
    {
        map->offset_x = 0;
        map->offset_y = 0;
    }

}

void    ft_updtxy(t_map *map, int num)
{
    if (map->offset_y >= num)
    {
        map->offset_x++;
        map->offset_y = 0;
    }
}

void    ft_updtmap(t_map *map, int num)
{
    if (map->map)
        ft_arrmemdel((void **) map->map);
    ft_getmap(num, map);
}

int  subst(t_map *map, int num)
{
    int y;
    int x;
    int flag;

    ft_updtxy(map, num);
    x = map->offset_x;
    y = map->offset_y;
    flag = 0;
    while (flag++ < 4)
    {
        x += find_x(map->figs, flag - 1);
        y += find_y(map->figs, flag - 1);
        if (x >= num || map->map[x][y] != '.')
        {
            if (x >= num || (x >= num - 1 && y >= num))
            {
                ft_set(map, x, y);
                return ((int)ft_arrmemdel((void **)map->map));
            }
            map->offset_y++;
            ft_check_map(map, num);
            return (subst(map, num));
        }
        map->map[x][y] = map->sym;
    }
    return (++map->offset_y);
}

int ft_check_offset(t_map *map, int num, int flag)
{
    if (flag == 1) {
        if (map->offset_x > num - 1 || (map->offset_x >= num - 1 && map->offset_y >= num - 3))
            return (0);
        return (1);
    }
    else
    {
        if (map->previous && (map->previous->offset_x > num - 1 ||
        (map->previous->offset_x >= num - 1 && map->previous->offset_y >= num - 3)))
        {
            ft_set(map->previous, 0, 0);
            ft_arrmemdel((void **) map->previous->map);
            return (0);
        }
        return (1);
    }
}

int fillit(t_map *map, int num)
{
    while (map) {
        if (subst(map, num) != 0) {
            if (map->next && map->next->figs)
                map = map->next;
            else
                return (ft_remove(map));
            map->map = ft_arrcopy(map->previous->map);
        }
        else
        {
            if (!map->previous && !ft_check_offset(map, num, 1))
                return (0);
            if (!ft_check_offset(map, num, 2))
                map = map->previous->previous;
            else
                map = map->previous;
            ft_check_map(map, num);
        }
    }
    return (1);
}

int ft_check_type(t_map *map, int x, int y, int fig)
{
    int i;

    i = 0;
    while (!fig && y != 4 && map->figs[x][y] == '#')
    {
        y++;
        i++;
        if (i == 3)
            return (1);
    }
    while (fig && x != 4 && map->figs[x][y] == '#')
    {
        x++;
        i++;
        if (i == 3)
            return (1);
    }
    return (0);
}

int ft_get_type1(t_map *map)
{
    int x;
    int y;
    int type;

    type = 0;
    while (map)
    {
        y = 0;
        x = 0;
        while (map->figs[x][y] != '#')
        {
            while (y != 4 && map->figs[x][y] != '#')
                y++;
            if (y == 4) {
                x++;
                y = 0;
            }
        }
        type += ft_check_type(map, x, ++y, 0);
        map = map->next;
    }
    return (type);
}

int ft_get_type2(t_map *map)
{
    int x;
    int y;
    int type;

    type = 0;
    while (map)
    {
        x = 0;
        y = 0;
        while (map->figs[x][y] != '#')
        {
            while (y != 4 && map->figs[x][y] != '#')
                y++;
            if (y == 4) {
                x++;
                y = 0;
            }
        }
        type += ft_check_type(map, ++x, y, 1);
        map = map->next;
    }
    return (type);
}

int ft_count_type(t_map *map)
{
    int type_1;
    int type_2;

    type_1 = ft_get_type1(map);
    type_2 = ft_get_type2(map);
    if (type_2 > type_1 && type_2 <= 8)
        return (type_2);
    else if (type_1 > type_2 && type_1 <= 8)
        return (type_1);
    if (type_1 > type_2 && type_1 < 16 && type_1 > 8)
        return (8);
    else if (type_2 > type_1 && type_2 < 16 && type_2 > 8)
        return (8);
    return (0);
}

int main(int argc, char **argv)
{
    int ret;
    map *field;
    int rows;

    if (argc == 2)
	{
		if ((field = ft_input(argv[1])))
		{
    		ret = ft_lstsize(field);
			rows = ft_sqrt(ret * 4);
    		ret = ft_count_type(field);
			if (rows < ret)
				rows = ret;
			ft_getmap(rows, field);
			while (fillit(field, rows) == 0) {
    	    	ft_set(field, 0, 0);
    	    	ft_getmap(++rows, field);
    		}
		}
		else
			ft_putstr("error\n");
	}
	else
		ft_putstr("usage: ./fillit target_file\n");
    return 0;
}
