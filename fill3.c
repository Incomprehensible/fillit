/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bomanyte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 20:29:35 by bomanyte          #+#    #+#             */
/*   Updated: 2019/06/10 17:35:44 by crycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "fillit.h"


void    *ft_memalloc(size_t size)
{
    int                i;
    unsigned char    *ptr;

    i = 0;
    if (!(ptr = malloc(size)))
        return (0);
    while (size--)
    {
        *ptr++ = '\0';
        i++;
    }
    return (ptr - i);
}

void    ft_memdel(void **ap)
{
    if (ap)
        free(*ap);
    *ap = NULL;
}

char    *ft_strnew(size_t size)
{
    int        i;
    char    *str;

    i = 0;
    if (size == (size_t)-1)
        return (0);
    if (!(str = (char*)malloc(size + 1)))
        return (0);
    str[size] = '\0';
    while (size-- && (i = i + 1))
        *str++ = '\0';
    return (str - i);
}

void    ft_strdel(char **as)
{
    if (as)
    {
        ft_memdel((void **)as);
        as = NULL;
    }
}

char    *ft_strdup(const char *s1)
{
    int        sz;
    char    *ptr;

    sz = 0;
    while (s1[sz] != '\0')
        sz++;
    if (!(ptr = (char *)ft_memalloc(sz + 1)))
        return (0);
    while (*s1 != '\0')
        *ptr++ = *s1++;
    return (ptr - sz);
}

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

void	ft_lstdelone(map **alst)
{
    map *head;

    head = *alst;
    if (!alst)
        return ;
    ft_arrmemdel((void **)head->map);
    free(head);
    head = NULL;
}

void    ft_printlst(map *valid) {

    printf("\n%s\n", valid->map[0]);
    printf("%s\n", valid->map[1]);
    printf("%s\n", valid->map[2]);
    printf("%s\n", valid->map[3]);
    printf("%s\n", valid->map[4]);
    printf("%s\n", valid->map[5]);
 printf("%s\n", valid->map[6]);
    printf("%s\n", valid->map[7]);
    printf("%s\n", valid->map[8]);
    printf("%s\n", valid->map[9]);
}

void    ft_remove(map *alst)
{
    map *head;
    map *valid;
    map *further;

    valid = alst;
    alst = alst->previous;
    while (alst)
    {
        head = alst;
        ft_lstdelone(&head);
        alst = alst->previous;
    }
    if (valid->next) {
        further = valid->next;
        while (further)
        {
            ft_lstdelone(&further);
            further = further->next;
        }
    }
    valid->previous = NULL;
    head = NULL;
    ft_printlst(valid);
}

/*void    ft_clean(map *alst)
{
    map *head;

    while (alst)
    {
        head = alst;
        alst = alst->previous;
        //del(head->content, head->content_size);
        if (head->map)
           ft_arrmemdel((void **)head->map);
    }
    head = NULL;
}*/

/* map    *ft_clean(map **alst)
{
    map *head;
    map *valid;

    valid = *alst;
    *alst = (*alst)->next;
    while (alst && *alst)
    {
        head = *alst;
        *alst = (*alst)->next;
        //del(head->content, head->content_size);
        ft_arrmemdel((void **)head->map);
        free(head);
    }
    head = NULL;
    return (valid);
} */

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
    static int x = 0;
    int x1;
    static int y = 0;
    int temp;

    x1 = x;
    if (num == 0)
    {
        x = 0;
        x1 = 0;
        y = 0;
    }
    if (num != 0)
        y++;
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
    if (x1 == 3)
        y = 0;
    if (num == 0)
        return (0);
    return (x1 - temp);
}

int find_y(char **fig, int num)
{
    static int y = 0;
    static int x = 0;
    int y1;
    int temp;

    if (num == 0) {
        x = 0;
        y = 0;
        y1 = 0;
    }
    if (num != 0)
        y1 = y + 1;
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
    if (num == 0)
        return (0);
    return (y1 - temp);
}

void    ft_set(map *map, int x, int y)
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

size_t	ft_lstsize(map *begin_lst)
{
    size_t i;

    i = 0;
    while (begin_lst)
    {
        begin_lst = begin_lst->next;
        i++;
    }
    return (i);
}

int     ft_dotstate(map *map, int num)
{
    int x;
    int y;
    int n;
    int i;

    x = 0;
    y = 0;
    i = 0;
    if (map->offset_x && map->offset_y)
        return (1);
    n = ft_lstsize(map);
    while (x != num)
    {
        while (y != num)
        {
            if (map->map[x][y] == '.')
                i++;
            if (i == 4)
            {
                n--;
                i = 0;
            }
            y++;
        }
        x++;
        y = 0;
    }
    if (i - n >= 0)
        return (1);
    return (0);
}

void    ft_updtxy(map *map, int num)
{
    if (map->offset_y >= num)
    {
        map->offset_x++;
        map->offset_y = 0;
    }
}

void    ft_updtmap(map *map, int num)
{
    ft_arrmemdel((void **) map->map);
    ft_getmap(num, map);
}

int  subst(map *map, int num)
{
    int y;
    int x;
    int flag;

    if (!ft_dotstate(map, num))
        return (0);
    ft_updtxy(map, num);
    x = map->offset_x;
    y = map->offset_y;
    flag = 0;
    while (flag < 4)
    {
        if (flag < 4) {
            x += find_x(map->figs, flag);
            y += find_y(map->figs, flag);
        }
        if (x >= num || map->map[x][y] != '.')
        {
            if (x >= num || (x >= num - 1 && y >= num)) {
                ft_set(map, x, y);
                return ((int)ft_arrmemdel((void **)map->map));
            }
            map->offset_y++;
            ft_arrmemdel((void **)map->map);
            if (map->previous)
                map->map = ft_arrcopy(map->previous->map);
            else
                ft_getmap(num, map);
            return (subst(map, num));
        }
        map->map[x][y] = map->sym;
        printf("%s\n", map->map[0]);
        printf("%s\n", map->map[1]);
        printf("%s\n", map->map[2]);
        printf("%s\n", map->map[3]);
         printf("%s\n\n", map->map[4]);
        //printf("%s\n", map->map[5]);
        //printf("%s\n", map->map[6]);
        flag++;
    }
    map->offset_y++;
    return (1);
}

int fillit(map *map, int num) {
    printf("num is %d\n", num);
    while (map) {
        if (subst(map, num) != 0) {
            if (map->next && map->next->figs) {
                map = map->next;
            } else {
                ft_remove(map);
                return (1);
            }
            map->map = ft_arrcopy(map->previous->map);
        } else {
            if (!map->previous && map->offset_x >= num - 1)
                return (0);
            if (map->previous->offset_x >= num - 1 && map->previous->offset_y >= num - 1) {
                ft_set(map->previous, 0, 0);
                ft_arrmemdel((void **) map->previous->map);
                map = map->previous->previous;
                if (!map->previous)
                    ft_updtmap(map, num);
                else
                    map->map = ft_arrcopy(map->previous->map);
            } else {
                map = map->previous;
                if (!map->previous)
                    ft_updtmap(map, num);
                else
                    map->map = ft_arrcopy(map->previous->map);
            }
        }
    }
}

void    ft_splitfigs(map *lst, char **arr, int n)
{
    char **arr2;
    int i;
    int offset;
    int j;
    int m;

    i = 0;
    offset = 0;
    j = 0;
    m = 0;
    arr2 = (char **)malloc(sizeof(arr2) * 5);
    while (arr[0][i] != '\n') {
        offset++;
        i++;
    }
    i = 0;
    arr2[4] = NULL;
    while (i != 4)
    {
        arr2[i] = (char *)ft_memalloc(offset);
        while (arr2[i] && arr2[i][m - 1] != '\n' && m <= offset)
        {
            arr2[i][m] = arr[n][j];
            m++;
            j++;
        }
        arr2[i][m - 1] = '\0';
        i++;
        m = 0;
    }
    lst->figs = arr2;
}

void    ft_setfigs(map *map, char **arr, int num)
{
    int i;

    i = 0;
    ft_splitfigs(map, arr, i++);
    while (--num) {
        map = map->next;
        ft_splitfigs(map, arr, i);
        i++;
    }
    ft_arrmemdel((void **)arr);
}

map *ft_mklst2(int num)
{
    map *head;
    map *start;
    map *prev;

    head = (map *)malloc(sizeof(map));
    start = head;
    prev = head;
    head->map = 0;
    head->sym = 'A';
    ft_set(head, 0, 0);
    head->previous = NULL;
    head->next = NULL;
    while (--num) {
        head->next = (map *)malloc(sizeof(map));
        head->next->next = NULL;
        head = head->next;
        head->map = 0;
        ft_set(head, 0, 0);
        head->previous = prev;
        head->sym = head->previous->sym + 1;
        prev = head;
    }
    return (start);
}

char **ft_seprt(char *str, int num)
{
    int i;
    int j;
    int n;
    char **arr;

    n = 0;
    i = 0;
    j = 0;
    while (str[j] != '\n')
        j++;
    arr = (char **)ft_memalloc(sizeof(arr) * (num + 1));
    while (n < num)
    {
        if (!arr[n])
            arr[n] = (char *)ft_memalloc((j + 1) * 4);
        arr[n][i] = *str;
        if ((*str == '\n' && *(str + 1) == '\n') || *str == '\0')
        {
            arr[n][i] = '\0';
            n++;
            i = 0;
            str++;
        }
        else
            i++;
        str++;
    }
    return (arr);
}

int ft_get_type1(map *map, int num)
{
    int i;
    int x;
    int y;
    int type;

    type = 0;
    while (map)
    {
        i = 0;
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
        y++;
        while (y != 4 && map->figs[x][y] == '#')
        {
            y++;
            i++;
            if (i == 3)
                type++;
        }
        map = map->next;
    }
    return (type);
}

int ft_get_type2(map *map, int num)
{
    int i;
    int x;
    int y;
    int type;

    type = 0;
    while (map)
    {
        i = 0;
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
        x++;
        while (x != 4 && map->figs[x][y] == '#')
        {
            x++;
            i++;
            if (i == 3)
                type++;
        }
        map = map->next;
    }
    return (type);
}

int ft_count_type(map *map, int num)
{
    int type_1;
    int type_2;
    int type_3;

    type_1 = ft_get_type1(map, num);
    type_2 = ft_get_type2(map, num);
    type_3 = num - type_1 - type_2;
    if (type_1 && type_2 && type_3)
    {
        if (type_2 > type_1)
            return (type_2 + 1);
        else if (type_1 > type_2)
            return (type_1 + 1);
    }
    if (type_2 > type_1)
        return (type_2);
    else if (type_1 > type_2)
        return (type_1);
    return (0);
}

int is_sqr2(map *map, int num, int x, int y)
{
    int i;

    i = 1;
    if (map->figs[x][y] == '#') {
        x++;
        y--;
        {
            while (i != 4 && map->figs[x][y] == '#')
            {
                y++;
                i++;
            }
        }
    }
    if (i == 3)
        return (1);
    return (0);
}

int is_even(int ret)
{
    if (ret % 2 == 0)
        return (1);
    return (0);
}

int is_sqr(map *map, int ret)
{
    int ret2;
    int x;
    int y;

    ret2 = 0;
    while (map) {
        x = 0;
        y = 0;
        while (map->figs[x][y] != '#') {
            while (y < 4 && map->figs[x][y] != '#')
                y++;
            if (y == 4) {
                x++;
                y = 0;
            }
        }
        y++;
        ret2 += is_sqr2(map, ret, x, y);
        map = map->next;
    }
    //if (ret2 != ret)
        //return (ft_sqrt(ret * 4));
    //ret2 = ft_sqrt(ret * 4);
    //if (!(is_even((ret2 * ret2) - (ret * 4))))
        //++ret2;
    ret = ft_sqrt(ret * 4);
    if (ret2) {
        if (!(is_even((ret * ret) - (ret2 * 4))))
            ++ret;
    }
    return (ret);
}

int ft_get_fignum(char *s)
{
    int n;

    n = 0;
    while (*s)
    {
        if ((*s == '\n' && *(s + 1) == '\n') || *(s + 1) == '\0')
            n++;
        s++;
    }
    return (n);
}

int main(int argc, char **argv) {

    char buf[1000 + 1];
    int ret;
    int fd;
    char **figs;
    char *ex = "/Users/bomanyte/tryfillit/ex";
    map *field;
    int rows;

    fd = open(ex, O_RDONLY);
    while ((ret = read(fd, buf, 1000)) > 0)
        buf[ret] = '\0';
    ret = ft_get_fignum(buf);
    figs = ft_seprt(buf, ret);
    field = ft_mklst2(ret);
    ft_setfigs(field, figs, ret);
    rows = is_sqr(field, ret);
    ret = ft_count_type(field, ret);
    if (rows < ret)
        rows = ret;
    ft_getmap(rows, field);
    while (fillit(field, rows) == 0) {
        ft_set(field, 0, 0);
        ft_getmap(++rows, field);
    }
    return 0;
}
