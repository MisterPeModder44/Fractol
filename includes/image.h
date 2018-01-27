/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 08:20:34 by yguaye            #+#    #+#             */
/*   Updated: 2018/01/27 13:24:43 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMAGE_H
# define IMAGE_H

# include <stdint.h>
# include "fractol.h"

typedef union		u_color
{
	int32_t			value;
	int8_t			bytes[4];
}					t_color;

typedef struct		s_image
{
	char			*data;
	int				bpp;
	int				slen;
	int				endian;
	t_mlx_context	*ctx;
}					t_image;

t_color				set_color(t_image *img, int8_t r, int8_t g, int8_t b);

t_color				get_gradient(t_image *img, t_palette *p, double amount);

void				img_pixel_put(t_image *img, const int x, const int y,
		const t_color color);

#endif
