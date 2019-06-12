/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_fillit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bomanyte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 16:11:13 by bomanyte          #+#    #+#             */
/*   Updated: 2019/06/12 15:44:10 by bomanyte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define BUFF_SIZE 50

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

typedef struct		s_list
{
    void			*content;
    size_t			content_size;
    struct s_list	*next;
}					t_list;

void	ft_putchar(char c)
{
    write(1, &c, 1);
}

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

void	free_buf(char **buf, int i)
{
    while (i >= 0)
    {
        free(buf[i]);
        i--;
    }
    free(buf);
}

void	ft_putstr(char const *s)
{
    while (*s != '\0')
    {
        ft_putchar(*s);
        s++;
    }
}

t_list	*ft_lstnew(void const *content, size_t content_size)
{
    size_t			i;
    unsigned char	*p;
    unsigned char	*copy;
    t_list			*tmp;

    i = 0;
    p = (unsigned char *)content;
    if (!(copy = ft_memalloc(sizeof(unsigned char) * content_size)))
        return (0);
    if ((!(p) || !(content_size)))
    {
        copy = NULL;
        content_size = 0;
    }
    while ((copy && p[i] && i < content_size - 1) && (copy[i] = p[i]))
        i++;
    if (!(tmp = (t_list *)malloc(sizeof(t_list))))
    {
        free(copy);
        return (0);
    }
    tmp->content = (void *)copy;
    tmp->content_size = content_size;
    tmp->next = NULL;
    return (tmp);
}

void	ft_lstadd(t_list **alst, t_list *new)
{
    t_list *tmp;

    if (!(new))
        return ;
    if (*alst != 0)
    {
        if ((*alst)->next)
            tmp = (*alst)->next;
        if (!((*alst)->next))
            tmp = *alst;
        *alst = new;
        new->next = tmp;
    }
    else
        *alst = new;
}

size_t		ft_strlen(const char *str)
{
    size_t i;

    i = 0;
    while (*str != '\0')
    {
        i++;
        str++;
    }
    return (i);
}

char	*ft_strcat(char *s1, const char *s2)
{
    int i;

    i = 0;
    while (s1[i] != '\0')
        i++;
    while (*s2 != '\0')
    {
        s1[i] = *s2;
        i++;
        s2++;
    }
    s1[i] = '\0';
    return (s1);
}

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
    int i;

    i = 0;
    while (s1[i] != '\0')
        i++;
    while (*s2 != '\0' && n--)
    {
        s1[i] = *s2;
        i++;
        s2++;
    }
    s1[i] = '\0';
    return (s1);
}

char	*ft_strchr(const char *s, int c)
{
    int j;

    j = 0;
    while (s[j])
        j++;
    if (c == '\0')
    {
        while (*s != '\0')
            s++;
        return ((char *)s);
    }
    while (j--)
    {
        if (*s == c)
            return ((char *)s);
        s++;
    }
    return (0);
}

static t_list	*what_file(t_list **list, size_t fd)
{
    t_list *search;

    search = *list;
    while (search)
    {
        if (search->content_size == fd)
            return (search);
        search = search->next;
    }
    search = ft_lstnew("\0", 1);
    ft_lstadd(list, search);
    search->content_size = fd;
    return (search);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
    unsigned char	*p;
    unsigned char	*q;

    p = (unsigned char *)src;
    q = (unsigned char *)dst;
    while (n--)
    {
        *q = *p;
        q++;
        p++;
    }
    return (dst);
}

static void		lstremovis(t_list **alst, size_t this)
{
    t_list *remove;
    t_list *lucky;

    if (*alst)
    {
        lucky = *alst;
        remove = *alst;
        while (remove)
        {
            if (remove->content_size == this)
                break ;
            lucky = remove;
            remove = remove->next;
        }
        lucky->next = remove->next;
        free(remove->content);
        free(remove);
        remove = NULL;
    }
}

static void		*new_content(char *safe, char *buf, size_t size)
{
    char *str;

    str = ft_strnew(ft_strlen(safe) + size + 1);
    str = ft_strcat(str, safe);
    str = ft_strncat(str, buf, size);
    return (str);
}

static void		create_line(char **line, t_list *list, int *bit)
{
    char	*str;
    char	*safe;
    size_t	size;

    safe = list->content;
    if ((str = ft_strchr(list->content, '\n')))
    {
        size = str - safe;
        *line = (char *)ft_strnew(size + 1);
        *line = ft_memcpy(*line, safe, size);
        list->content = ft_strdup(str + 1);
        free(safe);
    }
    else if ((size = ft_strlen(list->content)) != 0)
    {
        *line = (char *)ft_strnew(size + 1);
        *line = ft_memcpy(*line, safe, size);
        list->content = ft_strnew(1);
        free(safe);
        *bit = size;
    }
}

int				get_next_line(const int fd, char **line)
{
    char			buf[BUFF_SIZE + 1];
    char			*safe_file;
    static t_list	*list;
    t_list			*file;
    int				size;

    if (fd < 0 || !(line) || (read(fd, buf, 0) < 0))
        return (-1);
    file = what_file(&list, fd);
    size = ft_strlen(file->content);
    while (!ft_strchr(file->content, '\n') && (size = read(fd, buf, BUFF_SIZE)))
    {
        safe_file = file->content;
        file->content = new_content(safe_file, buf, size);
        free(safe_file);
    }
    create_line(line, file, &size);
    if (size != 0)
        return (1);
    lstremovis(&list, fd);
    if (list == file && list->next == NULL)
        list = NULL;
    return (0);
}

size_t	ft_lstsize(map *begin_lst)
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

void	ft_add_to_end_2lst(map **start, map *new)
{
    map *list;

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

map		*ft_new_elem2lst(char **buf)
{
    map *new;
    int i;

    if ((new = (map *)malloc(sizeof(map))))
    {
        new->sym = 'A';
        new->offset_x = 0;
        new->offset_y = 0;
        new->next = NULL;
        new->previous = NULL;
        new->map = NULL;
        i = 0;
        if ((new->figs = (char **)malloc(sizeof(char *) * 4)))
        {
            while(i < 4)
            {
                if (!(new->figs[i] = ft_strdup(buf[i])))
                {
                    free_buf(new->figs, i);
                    return (NULL);
                }
                i++;
            }
        }
    }
    return (new);
}

static char	**fill_buf(int fd)
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

static int		check_end(fd)
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

void	ft_lstdel_one(map **alst)
{
    map *head;

    head = *alst;
    if (head->map)
        ft_arrmemdel((void **)head->map);
    free_buf(head->figs, 3);
    free(head);
    head = NULL;
}

int    ft_printlst(map *valid) {
    int i;

    i = 0;
    while (valid->map[i])
    {
        ft_putstr(valid->map[i]);
        ft_putchar('\n');
        i++;
    }
    return (1);
}

int    ft_remove(map *alst)
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
/*    if (valid->next) {
        further = valid->next;
        while (further)
        {
            ft_lstdel_one(&further);
            further = further->next;
        }
    }*/
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

size_t	ft_real_lstsize(map *begin_lst)
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

int     ft_dotstate(map *map, int x, int y, int num)
{
    int i;

    i = 0;
    //if (map->offset_x && map->offset_y)
        //return (1);
    //n = ft_real_lstsize(map);
    while (x < num)
    {
        while (x < num && y < num)
        {
            if (map->map[x][y] == '.')
                i++;
            if (i == 4)
                return (1);
            y++;
        }
        x++;
        y = 0;
    }
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
    if (map->map)
        ft_arrmemdel((void **) map->map);
    ft_getmap(num, map);
}

/*int ft_find(map *map, int flag, int num, int ch)
{
    static int x = 0;
    static int y = 0;

    ft_updtxy(map, num);
    if (!map->offset_y)
        y = map->offset_y;
    if (ch && map->offset_y && flag == 1)
        y++;
    x = map->offset_x;
    printf("x is %d y is %d\n", x, y);
    if (!(ft_dotstate(map, x, y, num)))
        return (num);
    if (!ch) {
        while (map->map[x] && map->map[x][y] != '.') {
            while (map->map[x][y] && map->map[x][y] != '.')
                y++;
            if (map->map[x][y] == '.')
                break;
            x++;
            y = 0;
        }
    }
    //map->offset_x = x;
    //map->offset_y = y;
    if (flag == 1)
        return (x);
    else
        return (y);
} */

/*int  subst(map *map, int num)
{
    int y;
    int x;
    int flag;


    flag = 0;
    x = ft_find(map, 1, num, flag);
    y = ft_find(map, 2, num, flag);
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
}*/

void ft_check_map(map *map, int num)
{
    ft_arrmemdel((void **)map->map);
    if (!map->previous)
        ft_getmap(num, map);
        //ft_updtmap(map, num);
    else
        map->map = ft_arrcopy(map->previous->map);
}

int  subst(map *map, int num)
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

int ft_check_offset(map *map, int num, int flag)
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

int fillit(map *map, int num)
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

int ft_check_type(map *map, int x, int y, int fig)
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

int ft_get_type1(map *map)
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

int ft_get_type2(map *map)
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

int ft_count_type(map *map)
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

int main(int argc, char **argv) {

    int ret;
    map *field;
    int rows;

    argc = 2;
    argv[1] = "/Users/bomanyte/tryfillit/tryfillit/ex";
    if (argc != 2)
        return (0);
    field = ft_input(argv[1]);
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
    return 0;
}
