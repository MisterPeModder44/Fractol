/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 08:22:24 by yguaye            #+#    #+#             */
/*   Updated: 2018/04/09 16:25:17 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "image.h"

t_color				set_color(t_image *img, uint8_t r, uint8_t g, uint8_t b)
{
	t_color			c;

	if (img->endian)
	{
		c.bytes[0] = 0;
		c.bytes[1] = r;
		c.bytes[2] = g;
		c.bytes[3] = b;
	}
	else
	{
		c.bytes[3] = 0;
		c.bytes[2] = r;
		c.bytes[1] = g;
		c.bytes[0] = b;
	}
	return (c);
}
