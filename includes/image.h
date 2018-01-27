/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 08:20:34 by yguaye            #+#    #+#             */
/*   Updated: 2018/01/27 14:52:43 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMAGE_H
# define IMAGE_H

# include <stdint.h>
# include "palette.h"

typedef union		u_color
{
	int32_t			value;
	int8_t			bytes[4];
}					t_color;

typedef struct		s_image
{
	void			*img_ptr;
	char			*data;
	int				bpp;
	int				slen;
	int				endian;
}					t_image;

t_color				set_color(t_image *img, int8_t r, int8_t g, int8_t b);

t_color				get_gradient(t_image *img, t_palette *p, double amount);

#endif
