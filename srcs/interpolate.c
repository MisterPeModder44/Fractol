/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpolate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 13:23:18 by yguaye            #+#    #+#             */
/*   Updated: 2018/01/27 13:23:39 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

int8_t				interpolate(uint8_t c1, uint8_t c2, double hue)
{
	if (c2 < c1)
		return ((int8_t)(-((int32_t)((c1 - c2) * hue + c2)) + 255));
	return ((c2 - c1) * hue + c1);
}
