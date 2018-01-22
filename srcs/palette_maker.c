/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   palette_maker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 17:09:08 by yguaye            #+#    #+#             */
/*   Updated: 2018/01/22 08:49:09 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "palette.h"
#include <stdio.h>

#define SCALE_POS(x, m, s) ((uint32_t)((double)x / (double)m * (double)s))

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

int8_t			interpolate(uint8_t c1, uint8_t c2, double hue)
{
	if (c2 < c1)
		return ((int8_t)(-((int32_t)((c1 - c2) * hue + c2)) + 255));
	return ((c2 - c1) * hue + c1);
}
static void			make_gradient(t_palette *pal, t_color_point *p1,
		t_color_point *p2)
{
	uint32_t		pos1;
	uint32_t		pos2;
	uint32_t		i;
	double			size;

	i = 0;
	pos1 = (uint32_t)((double)(pal->size * p1->pos) / (double)pal->max_hue);
	pos2 = (uint32_t)((double)(pal->size * p2->pos) / (double)pal->max_hue);
	size = pos2 - pos1;
	printf("==\nsize: %.1f\ni: %u\n", size, i);
	printf("color 1: 0x%.2hhx%.2hhx%.2hhx\n", p1->r, p1->g, p1->b);
	printf("color 2: 0x%.2hhx%.2hhx%.2hhx\n", p2->r, p2->g, p2->b);
	//	if (p1->pos != 0)
	//		--i;
	while (i + pos1 < pos2)
	{
		pal->reds[i + pos1] = interpolate(p1->r, p2->r, ((double)i / size));
		pal->blues[i + pos1] = interpolate(p1->g, p2->g, ((double)i / size));
		pal->greens[i + pos1] = interpolate(p1->b, p2->b, ((double)i / size));
		//pal->greens[i] = interpolate(p1->g, p2->g, ((double)i / size));
		//pal->blues[i] = interpolate(p1->b, p2->b, ((double)i / size));
		//pal->reds[i] = (p2->r - p1->r) * ((double)i / size) + p1->r;
		//pal->greens[i] = (p2->g - p1->g) * ((double)i / size) + p1->g;
		//pal->blues[i] = (p2->b - p1->b) * ((double)i / size) + p1->b;
		printf("color at %u: 0x%.2hhx%.2hhx%.2hhx\n", i + pos1, pal->reds[i], pal->greens[i], pal->blues[i]);
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
