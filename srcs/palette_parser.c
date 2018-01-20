/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   palette_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 12:00:48 by yguaye            #+#    #+#             */
/*   Updated: 2018/01/20 16:53:26 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft_base/stringft.h>
#include "fractol.h"
#include <stdio.h>

static void			del_color_point(t_color_point *point)
{
	free(point);
}

static t_list		*make_palette_lst(char ***tab, size_t len)
{
	size_t			i;
	t_list			*lst;
	t_list			*tmp;

	i = 0;
	lst = NULL;
	while (i < len)
	{
		if (!(tmp = get_color_point((*tab)[i])))
		{
			printf("break\n");
			fflush(stdout);
			if (lst)
				ft_lstdel(&lst, (void (*)(void *, size_t))&del_color_point);
			if (*tab)
				ft_strtabdel(tab);
			return (NULL);
		}
		ft_lstadd(&lst, tmp);
		++i;
	}
	return (lst);
}

static t_list		*get_palette_colors(const char *format, uint32_t *dim)
{
	char			**tab;
	size_t			len;
	t_list			*lst;

	printf("format: %s\n", format);
	if (!format)
		return (NULL);
	tab = ft_strsplit(format, ';');
	if (!(len = ft_strtablen(tab)))
		return (NULL);
	if (!get_size(tab, len, dim))
	{
		dim[0] = 10;
		dim[1] = 100;
	}
	else
		--len;
	if (!(lst = make_palette_lst(&tab, len)))
		return (NULL);
	ft_strtabdel(&tab);
	return (lst);
}

t_palette			*parse_palette(const char *format)
{
	t_list			*lst;
	t_list			*l;
	uint32_t		dim[2];
	t_color_point	*colo;

	if (!(lst = get_palette_colors(format, dim)))
	{
		printf("Invalid palette!\n");
		return (NULL);
	}
	l = lst;
	printf("palette max hue: %d\npalette size: %d\n", dim[0], dim[1]);
	while (l)
	{
		colo = l->content;
		printf("color point: value=0x%.2hhX%.2hhX%.2hhX, type=%d, pos=%u\n",
				colo->r, colo->g, colo->b, colo->type, colo->pos);
		l = l->next;
	}
	ft_lstdel(&lst, (void (*)(void *, size_t))&del_color_point);
	return (NULL);
}
