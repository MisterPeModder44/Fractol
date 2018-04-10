/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 08:22:05 by yguaye            #+#    #+#             */
/*   Updated: 2018/04/10 12:52:49 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "fractol.h"
#include "clbin.h"

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

static void			scale_coords(t_cpx *p, t_window *win, float x, float y)
{
	t_fractal		*frac;
	float			tx;
	float			ty;
	float			start_x;
	float			start_y;

	frac = win->extra;
	start_x = frac->x_min * win->ctx->mouse_ax;
	start_y = frac->y_min * win->ctx->mouse_ay;
	tx = x / (float)win->width * (frac->x_max - frac->x_min) + start_x;
	ty = y / (float)win->height * (frac->y_max - frac->y_min) + start_y;
	p->re = (3.5 * tx) / frac->x_max - 2.5;
	p->im = (2 * ty) / frac->y_max - 1;
}

static t_cpx		*make_cpx_tab(t_window *win, t_cpx *c)
{
	size_t			size;
	t_cpx			*tab;
	t_cpx			point;
	uint32_t		y;
	uint32_t		x;

	size = win->height * win->width;
	if (!(tab = (t_cpx *)malloc(sizeof(t_cpx) * size)))
		return (NULL);
	point = c ? *c : (t_cpx) {.re = 0, .im = 0};
	y = 0;
	while (y < win->height)
	{
		x = 0;
		while (x < win->width)
		{
			scale_coords(&point, win, x, y);
			tab[y * win->width + x] = point;
			++x;
		}
		++y;
	}
	return (tab);
}

static void			draw_fractal_pixels(t_window *win, t_clfloat *ret)
{
	uint32_t		y;
	uint32_t		x;

	y = 0;
	while (y < win->height)
	{
		x = 0;
		while (x < win->width)
		{
			win_pixel_put(win, x, y, get_gradient(win->img, win->ctx->palette,
						ret[x + y * win->width]));
			++x;
		}
		++y;
	}
}

void				draw_fractal(t_window *win, t_mlx_context *ctx)
{
	t_cpx			*tab;
	t_jfrac			frac;
	t_opencl_ctx	*clx;
	t_clfloat		*ret;

	clx = ctx->cl_ctx;
	if (!(tab = make_cpx_tab(win, NULL)))
		return ;
	init_frac_mem(&frac, ((t_fractal *)win->extra)->type,
			win->width * win->height, ((t_fractal *)win->extra)->iter);
	set_frac_mem(ctx->cl_ctx, &frac, tab,
			(t_cpx){.re = ctx->mouse_lx, .im = ctx->mouse_ly});
	if (!(ret = run_kernel(R_KRN(clx, CL_MANDEL_ID), R_ARG(clx, CL_MANDEL_ID),
					clx->cmd_queue, win->width * win->height)))
		return ;
	draw_fractal_pixels(win, ret);
	put_gradient_bar(win);
}
