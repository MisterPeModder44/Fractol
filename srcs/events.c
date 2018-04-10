/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 10:54:10 by yguaye            #+#    #+#             */
/*   Updated: 2018/04/10 16:12:19 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"

int			on_close_window(t_mlx_context *ctx)
{
	quit_fractol(ctx, NULL);
	return (0);
}

static void	zoom(t_mlx_context *ctx, t_bool zoom_in,
		t_fractal *frac)
{
	double		distx;
	double		disty;

	distx = (frac->x_max - frac->x_min) / 50.;
	disty = (frac->y_max - frac->y_min) / 50.;
	if (zoom_in)
	{
		frac->x_min += distx;
		frac->y_min += disty;
		frac->x_max -= distx;
		frac->y_max -= disty;
	}
	else
	{
		frac->x_min -= distx;
		frac->y_min -= disty;
		frac->x_max += distx;
		frac->y_max += disty;
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
		zoom(ctx, button == SCROLL_UP_KEY, frac);
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
		zoom(ctx, key == PLUS_KEY || key == SCROLL_UP_KEY, frac);
	else if (key == R_KEY)
		reset_zoom(ctx, win, frac);
	else if (key == LBRACKET_KEY || key == RBRACKET_KEY)
		change_iter_level(ctx, key == RBRACKET_KEY, frac);
	else if (key == L_KEY)
	{
		ctx->locked = !ctx->locked;
		if (!ctx->locked)
		{
			ctx->mouse_lx = ctx->mouse_ax;
			ctx->mouse_ly = ctx->mouse_ay;
			draw_fwindow(ctx->windows);
		}
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
	if (!ctx->locked)
	{
		ctx->mouse_lx = ctx->mouse_ax;
		ctx->mouse_ly = ctx->mouse_ay;
	}
	ctx->mouse_px = x;
	ctx->mouse_py = y;
	draw_fwindow(ctx->windows);
	return (0);
}
