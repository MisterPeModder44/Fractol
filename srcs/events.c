/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 10:54:10 by yguaye            #+#    #+#             */
/*   Updated: 2018/04/09 16:02:43 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"
#include <stdio.h>

int			on_close_window(t_mlx_context *ctx)
{
	quit_fractol(ctx, NULL);
	return (0);
}

static void	zoom(t_mlx_context *ctx, t_bool zoom_in, t_window *win,
		t_fractal *frac)
{
	double		distx;
	double		disty;

	distx = (frac->x_max - frac->x_min) / 2.;
	disty = (frac->y_max - frac->y_min) / 2.;
	if (zoom_in)
	{
		frac->x_min += distx / 2.;
		frac->y_min += disty / 2.;
		frac->x_max -= distx / 2.;
		frac->y_max -= disty / 2.;
	}
	else
	{
		if ((frac->x_min -= distx) < .0)
			frac->x_min = .0;
		if ((frac->y_min -= disty) < .0)
			frac->y_min = .0;
		if ((frac->x_max += distx) > (double)win->width)
			frac->x_max = win->width;
		if ((frac->y_max += disty) > (double)win->height)
			frac->y_max = win->height;
	}
	draw_fwindow(ctx->windows);
}

int			on_mouse_pressed(int button, int x, int y, t_mlx_context *ctx)
{
	t_window	*win;
	t_fractal	*frac;

	y = 0;
	x = 0;
	if (button == SCROLL_UP_KEY || button == SCROLL_DOWN_KEY)
	{
		win = (t_window *)ctx->windows->content;
		frac = win->extra;
		zoom(ctx, button == SCROLL_UP_KEY, win, frac);
	}
	return (0);
}

int			on_key_released(int key, t_mlx_context *ctx)
{
	t_window	*win;
	t_fractal	*frac;

	win = (t_window *)ctx->windows->content;
	frac = win->extra;
	if (key == ESC_KEY)
		on_close_window(ctx);
	else if (key == PLUS_KEY || key == MINUS_KEY)
	{
		zoom(ctx, key == PLUS_KEY || key == SCROLL_UP_KEY, win, frac);
	}
	else if (key == R_KEY)
	{
		frac->x_min = (double)win->pos_x;
		frac->y_min = (double)win->pos_y;
		frac->x_max = (double)(win->pos_x + win->width);
		frac->y_max = (double)(win->pos_y + win->height);
		draw_fwindow(ctx->windows);
	}
	return (0);
}

int			on_mouse_movement(int x, int y, t_mlx_context *ctx)
{
	double	w;
	double	h;

	w = (double)((t_window *)ctx->windows->content)->width;
	h = (double)((t_window *)ctx->windows->content)->height;
	ctx->mouse_ax = clamp(x, 0, w) / w;
	ctx->mouse_ay = clamp(y, 0, h) / h;
	ctx->mouse_px = x;
	ctx->mouse_py = y;
	draw_fwindow(ctx->windows);
	return (0);
}
