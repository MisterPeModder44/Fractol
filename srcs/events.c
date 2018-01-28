/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 10:54:10 by yguaye            #+#    #+#             */
/*   Updated: 2018/01/28 09:31:12 by yguaye           ###   ########.fr       */
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

int			on_key_released(int key, t_mlx_context *ctx)
{
	t_window	*win;
	t_fractal	*frac;

	if (key == ESC_KEY)
		on_close_window(ctx);
	else if (key == PLUS_KEY || key == MINUS_KEY)
	{
		win = (t_window *)ctx->windows->content;
		frac = win->extra;
		zoom(ctx, key == PLUS_KEY, win, frac);
	}
	return (0);
}

int			on_mouse_movement(int x, int y, t_mlx_context *ctx)
{
	double	w;
	double	h;

	w = (double)((t_window *)ctx->windows->content)->width;
	h = (double)((t_window *)ctx->windows->content)->height;
	y = y < 0 ? 0 : y;
	x = x < 0 ? 0 : x;
	ctx->mouse_x = (x > w ? w : (double)x) / w;
	ctx->mouse_y = (y > h ? h : (double)y) / h;
	return (0);
}
