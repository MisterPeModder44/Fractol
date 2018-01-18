/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   palette.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 14:41:28 by yguaye            #+#    #+#             */
/*   Updated: 2018/01/18 18:34:43 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "fractol.h"
#include "image.h"

static uint8_t		*make_gradient(uint8_t c1, uint8_t c2, uint32_t size)
{
	uint8_t			*band;
	uint32_t		i;

	if (!(band = (uint8_t *)malloc(sizeof(uint8_t) * size)))
		return (NULL);
	i = 0;
	while (i < size)
	{
		band[i] = (c2 - c1) * ((double)i / (double)size) + c1;
		++i;
	}
	return (band);
}

t_palette			*new_palette(uint8_t *color1, uint8_t *color2, uint32_t size)
{
	t_palette		*palette;

	if (!(palette = (t_palette *)malloc(sizeof(t_palette))))
		return (NULL);
	if (!(palette->reds = make_gradient(color1[0], color2[0], size)))
		return (NULL);
	if (!(palette->greens = make_gradient(color1[1], color2[1], size)))
		return (NULL);
	if (!(palette->blues = make_gradient(color1[2], color2[2], size)))
		return (NULL);
	palette->size = size;
	return (palette);
}

void				del_palette(t_palette **palette)
{
	uint32_t		i;

	if (!*palette)
		return ;
	i = 0;
	free((*palette)->reds);
	free((*palette)->greens);
	free((*palette)->blues);
	free(*palette);
	palette = NULL;
}

t_color				*get_gradient(t_image *img, t_palette *p, t_color *c,
		double amount)
{
	uint32_t		pos;

	pos = (uint32_t)(amount * p->size);
	set_color(img, c, (int8_t[3]){p->reds[pos], p->greens[pos], p->blues[pos]});
	return (c);
}
