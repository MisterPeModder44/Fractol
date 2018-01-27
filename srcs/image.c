/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 08:22:05 by yguaye            #+#    #+#             */
/*   Updated: 2018/01/27 16:35:14 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <libft_math/complex.h>
#include <stdio.h>
#include "fractol.h"

static void			mandelbrot_pixel(t_image *img, t_cpx *point, t_color *color,
		t_palette *pal)
{
	double			x;
	double			y;
	int				i;
	double			tmp;

	x = .0;
	y = .0;
	i = 0;
	while (x * x + y * y < 4 && i < 1000)
	{
		tmp = x * x - y * y + point->re;
		y = 2 * x * y + point->im;
		x = tmp;
		++i;
	}
	if (i == 1000)
		*color = set_color(img, 0, 0, 0);
	else
		*color = get_gradient(img, pal, (double)i / 1000.0);
}

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
				(double)x / (double)win->width);
		while (y < win->height)
		{
			win_pixel_put(win, x, y, color);
			++y;
		}
		++x;
	}
}

static void			scale_coords(t_cpx *p, t_window *win, double x, double y)
{
	t_fractal		*frac;
	double			tx;
	double			ty;

	frac = win->extra;
	tx = x / (double)win->width * (frac->x_max - frac->x_min) + frac->x_min;
	ty = y / (double)win->height * (frac->y_max - frac->y_min) + frac->y_min;
	*p = (t_cpx){.re = (3.5 * tx) / frac->x_max - 2.5, .im = (2 * ty) / frac->y_max - 1};
}

void				draw_fractal(t_window *win)
{
	t_cpx			point;
	uint32_t		y;
	uint32_t		x;
	t_color			color;

	y = .0;
	//dim[0] = win->width;
	//dim[1] = win->height;
	while (y < win->height)
	{
		x = .0;
		while (x < win->width)
		{
			scale_coords(&point, win, x, y);
			//point = (t_cpx){.re = (3.5 * x) / dim[0] - 2.5, .im = (2 * y) /
			//	dim[1] - 1};
			mandelbrot_pixel(win->img, &point, &color, ((t_fractal *)win->extra)->palette);
			win_pixel_put(win, x, y, color);
			++x;
		}
		++y;
	}
	put_gradient_bar(win);
}
