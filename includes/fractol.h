/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 08:20:17 by yguaye            #+#    #+#             */
/*   Updated: 2018/01/20 17:03:45 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "palette.h"

typedef struct		s_mlx_context
{
	void			*mlx;
	void			*win;
	uint32_t		width;
	uint32_t		height;
	void			*img;
	t_palette		*palette;
}					t_mlx_context;

typedef enum		e_interpolation
{
	LINEAR = 1,
}					t_interpolation;

typedef struct		s_color_point
{
	uint8_t			r;
	uint8_t			g;
	uint8_t			b;
	t_interpolation	type;
	uint32_t		pos;
}					t_color_point;

void				put_fractol_render(t_mlx_context *ctx);
void				quit_fractol(t_mlx_context *ctx, const char *reason);

#endif
