/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   palette_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 12:00:48 by yguaye            #+#    #+#             */
/*   Updated: 2018/02/24 15:47:05 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft_base/stringft.h>
#include "palette.h"

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

	if (!format)
		return (NULL);
	tab = ft_strsplit(format, ';');
	if (!(len = ft_strtablen((const char **)tab)))
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

void				sort_color_list(t_list **begin_list)
{
	t_list	**curr;
	t_list	*tmp;
	t_list	*tmp2;

	curr = begin_list;
	if (!*begin_list)
		return ;
	while (*curr && (*curr)->next)
	{
		if (((t_color_point *)(*curr)->content)->pos >
				((t_color_point *)(*curr)->next->content)->pos)
		{
			tmp = *curr;
			tmp2 = (*curr)->next;
			(*curr)->next = (*curr)->next->next;
			*curr = tmp2;
			(*curr)->next = tmp;
			curr = begin_list;
		}
		else
			curr = &(*curr)->next;
	}
}

t_palette			*parse_palette(const char *format)
{
	t_list			*lst;
	uint32_t		dim[2];
	t_palette		*palette;

	if (!(lst = get_palette_colors(format, dim)))
		return (NULL);
	palette = NULL;
	if (val_palette(lst, dim[1], dim[0]))
	{
		sort_color_list(&lst);
		if (((t_color_point *)lst->content)->pos == 0)
		{
			palette = make_palette(lst, dim[1], dim[0]);
			ft_lstdel(&lst, (void (*)(void *, size_t))&del_color_point);
		}
	}
	return (palette);
}
