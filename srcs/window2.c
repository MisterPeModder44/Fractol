/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/28 08:30:55 by yguaye            #+#    #+#             */
/*   Updated: 2018/02/08 17:22:34 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void				draw_fwindow(t_list *win)
{
	t_window		*w;

	w = win->content;
	draw_window(w, w->ctx, (void (*)(t_window *, void *))
			((t_fractal *)w->extra)->draw);
}

t_window			*init_w(t_mlx_context *ctx, t_window *win)
{
	if (!win || !ctx)
		return (NULL);
	win->ctx = ctx;
	return (win);
}
