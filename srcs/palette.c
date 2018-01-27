/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   palette.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 14:41:28 by yguaye            #+#    #+#             */
/*   Updated: 2018/01/27 13:15:23 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "fractol.h"
#include "image.h"
#include <stdio.h>

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

t_color				get_gradient(t_image *img, t_palette *p,
		double amount)
{
	uint32_t		pos;

	pos = (uint32_t)(amount * p->size);
	return (set_color(img, p->reds[pos], p->greens[pos], p->blues[pos]));
}
