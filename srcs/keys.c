/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 18:02:57 by yguaye            #+#    #+#             */
/*   Updated: 2018/04/09 18:20:24 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"

void		reset_zoom(t_mlx_context *ctx, t_window *win, t_fractal *frac)
{
	frac->x_min = (double)win->pos_x;
	frac->y_min = (double)win->pos_y;
	frac->x_max = (double)(win->pos_x + win->width);
	frac->y_max = (double)(win->pos_y + win->height);
	draw_fwindow(ctx->windows);
}

void		change_iter_level(t_mlx_context *ctx, t_bool what, t_fractal *frac)
{
	if (what)
		frac->iter += 100;
	else
		frac->iter -= 100;
	if (frac->iter < 0)
		frac->iter = 0;
	draw_fwindow(ctx->windows);
}
