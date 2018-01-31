/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 08:22:05 by yguaye            #+#    #+#             */
/*   Updated: 2018/01/31 18:32:06 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdio.h>
#include "fractol.h"

static void			put_gradient_bar(t_window *win)
{
	uint32_t		x;
	t_color			black;
	t_color			color;
	uint32_t		y;

	x = 0;
	black = (t_color){.value = 0x00000000};
	while (x < win->width)
	{
		y = win->height - 20;
		win_pixel_put(win, x, y - 1, black);
		color = get_gradient(win->img, ((t_fractal *)win->extra)->palette,
				(float)x / (float)win->width);
		while (y < win->height)
		{
			win_pixel_put(win, x, y, color);
			++y;
		}
		++x;
	}
}

static void			scale_coords(t_cpx p, t_window *win, float x, float y)
{
	t_fractal		*frac;
	float			tx;
	float			ty;
	float			start_x;
	float			start_y;

	frac = win->extra;
	start_x = frac->x_min * win->ctx->mouse_x;
	start_y = frac->y_min * win->ctx->mouse_y;
	tx = x / (float)win->width * (frac->x_max - frac->x_min) + start_x;
	ty = y / (float)win->height * (frac->y_max - frac->y_min) + start_y;
	p[0] = (3.5 * tx) / frac->x_max - 2.5;
	p[1] = (2 * ty) / frac->y_max - 1;
}

void				draw_fractal(t_window *win, t_opencl_ctx *ctx)
{
	t_cpx			point;
	uint32_t		y;
	uint32_t		x;
	//t_color			color;

	y = .0;
	while (y < win->height)
	{
		x = .0;
		while (x < win->width)
		{
			scale_coords(point, win, x, y);
			julia_mandelbrot(point, ctx);
			//win_pixel_put(win, x, y, color);
			++x;
		}
		++y;
	}
	put_gradient_bar(win);
}
