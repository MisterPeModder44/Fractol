/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 10:54:10 by yguaye            #+#    #+#             */
/*   Updated: 2018/01/27 17:22:52 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"
#include <stdio.h>

int			on_close_window(t_mlx_context *ctx)
{
	quit_fractol(ctx, NULL);
	return (0);
}

int			on_key_released(int key, t_mlx_context *ctx)
{
	t_window	*win;
	t_fractal	*frac;
	double		distx;
	double		disty;

	if (key == ESC_KEY)
		on_close_window(ctx);
	else if (key == PLUS_KEY || key == MINUS_KEY)
	{
		win = (t_window *)ctx->windows->content;
		frac = win->extra;
		distx = (frac->x_max - frac->x_min) / 2.;
		disty = (frac->y_max - frac->y_min) / 2.;
		if (key == PLUS_KEY)
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
		draw_fwindow(ctx->windows, ctx);
	}
	return (0);
}
