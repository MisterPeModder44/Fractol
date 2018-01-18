/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 08:22:24 by yguaye            #+#    #+#             */
/*   Updated: 2018/01/18 11:07:14 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "image.h"

t_color				*set_color(t_image *img, t_color *c, int8_t *rgb)
{
	if (img->endian)
	{
		c->bytes[1] = rgb[0];
		c->bytes[2] = rgb[1];
		c->bytes[3] = rgb[2];
	}
	else
	{
		c->bytes[2] = rgb[0];
		c->bytes[1] = rgb[1];
		c->bytes[0] = rgb[2];
	}
	return (c);
}
