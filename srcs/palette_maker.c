/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   palette_maker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 17:09:08 by yguaye            #+#    #+#             */
/*   Updated: 2018/01/20 18:15:31 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "palette.h"
#include <stdio.h>

t_bool				val_palette(t_list *colors, uint32_t size, uint32_t mhue)
{
	t_color_point	*p;

	if (!colors || size == 0)
		return (FALSE);
	while (colors)
	{
		p = colors->content;
		if (p->pos > mhue || (p->type != -1 && p->type != 1))
			return (FALSE);
		colors = colors->next;
	}
	return (TRUE);
}

static t_bool		alloc_colors(t_palette *pal)
{
	if (!(pal->reds = (uint8_t *)malloc(sizeof(uint8_t) * pal->size)))
		return (FALSE);
	if (!(pal->greens = (uint8_t *)malloc(sizeof(uint8_t) * pal->size)))
	{
		free(pal->reds);
		return (FALSE);
	}
	if (!(pal->blues = (uint8_t *)malloc(sizeof(uint8_t) * pal->size)))
	{
		free(pal->reds);
		free(pal->greens);
		return (FALSE);
	}
	return (TRUE);
}

static t_palette	*unicolor_palette(t_palette *pal, t_color_point *color)
{
	uint32_t		i;

	i = 0;
	while (i < pal->size)
	{
		pal->reds[i] = color->r;
		pal->greens[i] = color->g;
		pal->blues[i] = color->b;
		++i;
	}
	return (pal);
}

static void			make_gradient(t_palette *pal, t_color_point *p1,
		t_color_point *p2)
{
	uint32_t		i;
	double			size;

	i = p1->pos;
	size = p2->pos - p1->pos;
	while (i < p2->pos)
	{
		pal->reds[i] = (p2->r - p1->r) * ((double)i / size) + p1->r;
		pal->greens[i] = (p2->g - p1->g) * ((double)i / size) + p1->g;
		pal->blues[i] = (p2->b - p1->b) * ((double)i / size) + p1->b;
		++i;
	}
}

t_palette			*make_palette(t_list *colors, uint32_t size, uint32_t mhue)
{
	t_palette		*pal;

	if (!(pal = (t_palette *)malloc(sizeof(t_palette))))
		return (NULL);
	pal->size = size;
	pal->max_hue = mhue;
	if (!alloc_colors(pal))
	{
		free(pal);
		return (NULL);
	}
	if (!colors->next)
		return (unicolor_palette(pal, (t_color_point *)colors->content));
	while (colors->next)
	{
		make_gradient(pal, colors->content, colors->next->content);
		colors = colors->next;
	}
	return (pal);
}
