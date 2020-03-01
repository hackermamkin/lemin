/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfreddie <gfreddie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 18:07:10 by gfreddie          #+#    #+#             */
/*   Updated: 2020/03/01 00:42:35 by gfreddie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


//#include "lemin.h"
#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <stdlib.h>
#include "libft/libft.h"

//char  MARKERS[12] = "##start##end"

typedef struct      s_pointlist
{
    char            last_room_identificator;
    int             level;
    char            *start_end;
    char            *name_point;
    int             coordinates[2];
    char            **links;
}                   t_pointlist;

int             search_list(t_pointlist *point_info, char *search_name)
{
    int     index;

    index = 0;
    ft_putstr("start_search\n");
    while (point_info[index].last_room_identificator != 'E' && ft_strcmp(point_info[index].name_point, search_name) != 0)
        index++;
    ft_putnbr(index);
    ft_putstr("index | search_steps\n");
    if (point_info[index].last_room_identificator == 'E' && ft_strcmp(point_info[index].name_point, search_name) != 0)
    {
        ft_putstr("ERROR\n");
        return (-1);
    }
    ft_putstr("all_good\n");
    return (index);
}

int             is_it_numbers_on_str(char *str)
{
    int     i;

    i = 0;
    while (str[i])
    {
        if (!(str[i] >= '0' && str[i] <= '9') && str[i] != ' ' && str[i] != '\t')
            return (0);
        i++;
    }
    return (1);
}
int             for_each(char **str)
{
    int     index;

    index = 0;
    while (str[index] != NULL && is_it_numbers_on_str(str[index]))
        index++;
    if (str[index] == NULL)
        return (1);
    return (0);
}

int             len_double_star_char(char **str)
{
    int     index;

    index = 0;
    while (str[index] != NULL)
        index++;
    return (index);
}

t_pointlist     *list_creation()
{
    t_pointlist     *new_list;

    new_list = (t_pointlist *)malloc(sizeof(t_pointlist) * (2));
    new_list[1].last_room_identificator = 'E';
    return (new_list);
}

t_pointlist     *struct_calc(t_pointlist *main_list, t_pointlist *plus_struct)
{
    int             len_list;
    int             index;
    t_pointlist     *new_list;

    len_list = 0;
    index = 0;
    while (main_list[len_list].last_room_identificator != 'E')
        len_list++;
    new_list = (t_pointlist *)malloc(sizeof(t_pointlist) * (len_list + 2));
    new_list[len_list + 1].last_room_identificator = 'E';
    while (index <= len_list)
    {
        if (main_list[index].last_room_identificator == 'E')
        {
            plus_struct[0].last_room_identificator = 'S';
            new_list[index] = plus_struct[0];
        }
        else
        {
            main_list[index].last_room_identificator = 'S';
            new_list[index] = main_list[index];
        }
        index++;
    }
    return(new_list);
}

char            **plus_on_double_star_char(char **old, char *new_elem)
{
    int     i;
    int     index;
    int     len;
    char    **new_mas;

    index = len_double_star_char(old);
    new_mas = (char **)malloc(sizeof(char *) * (index + 2));
    new_mas[++index] = NULL;
    i = 0;
    while (i <= index - 1)
    {
        len = ft_strlen(old[i]);
        new_mas[i] = (char *)malloc(sizeof(char) * (len + 1));
        new_mas[i][len] = '\0';
        i++;
    }
    len = ft_strlen(new_elem);
    new_mas[i] = (char *)malloc(sizeof(char) * (len + 1));
    new_mas[i][len] = '\0';
    i = 0;
    len = 0;
    while (i <= index - 1)
    {
        while (old[i][len] != '\0')
        {
            new_mas[i][len] = old[i][len];
            len++; 
        }
        len = 0;
        i++;
    }
    while (new_elem[len])
    {
        new_mas[i][len] = new_elem[len];
        len++;
    }
    return (new_mas);
}

int             main(int gc, char **gv)
{
    char            *str;
    char            **split;
    char            *markers;
    t_pointlist     *point_info;
    t_pointlist     *plus_part;
    int             ant_number;
    int             index;

    index = ft_strlen("##start##end");
    markers = (char *)malloc(sizeof(char) * (index + 1));
    markers[index] = '\0';
    markers[0] = '#';
    markers[1] = '#';
    markers[2] = 's';
    markers[3] = 't';
    markers[4] = 'a';
    markers[5] = 'r';
    markers[6] = 't';
    markers[7] = '#';
    markers[8] = '#';
    markers[9] = 'e';
    markers[10] = 'n';
    markers[11] = 'd';
    index = 0;
   /* ft_putstr("sdl");
    split = ft_strsplit(markers, '#');
    ft_putstr("gggg");
    printf("%s\n",split[0]);
    while (split[index] != NULL)
        ft_putstr(split[index++]);*/
    point_info = (t_pointlist *)malloc(sizeof(t_pointlist) * (2));
    point_info[0].last_room_identificator = 'S';
    point_info[1].last_room_identificator = 'E';
    while (get_next_line(0, &str) > 0) //число муравьев
    {
        ft_putstr(str);
        ft_putstr("\n");
        if(ft_strstr(markers, str))
        {
            ft_putstr("ERROR\n");
            return (0);
        }
        if (is_it_numbers_on_str(str))
        {
            ant_number = atoi(str);
            break;
        }
    }
    while (get_next_line(0, &str) > 0) //старт
    {
        ft_putstr(str);
        ft_putstr("\n");
        if (((int)ft_strstr(markers, str) - (int)markers) == 0 &&
            get_next_line(0, &str) > 0)
        {
            ft_putstr(str);
            ft_putstr("\n");
            split = ft_strsplit(str, ' ');

            point_info[0].start_end = "start";
            point_info[0].name_point = split[0];
            point_info[0].coordinates[0] = ft_atoi(split[1]);
            point_info[0].coordinates[1] = ft_atoi(split[2]);
            break;
        }
        if (((int)ft_strstr(markers, str) - (int)markers == 7) || (ft_strchr(str, '-') && str[0] != '#'))
        {
            ft_putstr("ERROR\n");
            break;
        }
    }
    while (get_next_line(0, &str) > 0) //конец и вершины+
    {
        ft_putstr(str);
        ft_putstr("\n");
        if (((int)ft_strstr(markers, str) - (int)markers) == 7 && 
            get_next_line(0, &str) > 0)
        {
            ft_putstr(str);
            ft_putstr("\n");
            plus_part = list_creation();
            split = ft_strsplit(str, ' ');
            plus_part[0].start_end = "end";
            plus_part[0].name_point = split[0];
            plus_part[0].coordinates[0] = ft_atoi(split[1]);
            plus_part[0].coordinates[1] = ft_atoi(split[2]);
            struct_calc(point_info, plus_part);
        }
        else if (is_it_numbers_on_str(str))
        {
            plus_part = list_creation();
            split = ft_strsplit(str, ' ');
            plus_part[0].start_end = "E";
            plus_part[0].name_point = split[0];
            plus_part[0].coordinates[0] = ft_atoi(split[1]);
            plus_part[0].coordinates[1] = ft_atoi(split[2]);
            struct_calc(point_info, plus_part);
        }
        else if ((split = ft_strsplit(str, '-')) && len_double_star_char(split) == 2)
        {
            ft_putstr("Links\n");
            point_info[search_list(point_info, split[0])].links = plus_on_double_star_char(point_info[search_list(point_info, split[0])].links, split[1]);
            ft_putstr("lol");
            ft_putstr(point_info[search_list(point_info, split[0])].links[0]);
            point_info[search_list(point_info, split[1])].links = plus_on_double_star_char(point_info[search_list(point_info, split[1])].links, split[0]);
        }
        /*if ((ft_strchr(str, '-') && str[0] != '#') || ((int)ft_strstr(markers, str) - (int)markers) == 0)
        {
            ft_putstr("ERROR\n");
            break;
        }*/
    }
    //ft_putstr("Link search start\n");
    /*while (get_next_line(0, &str) > 0)//линки
    {
        ft_putstr(str);
        ft_putstr("\n");
        if ((split = ft_strsplit(str, '-')) && len_double_star_char(split) == 2)
        {
            point_info[search_list(point_info, split[0])].links = plus_on_double_star_char(point_info[search_list(point_info, split[0])].links, split[1]);
            point_info[search_list(point_info, split[1])].links = plus_on_double_star_char(point_info[search_list(point_info, split[1])].links, split[0]);
        }
    }*/
    return (0);
}