/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/28 08:30:55 by yguaye            #+#    #+#             */
/*   Updated: 2018/04/09 18:19:05 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <mlx.h>
#include <libft_base/stringft.h>

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

static char			*get_fractal_name(t_window *win)
{
	t_fractype type;

	type = ((t_fractal *)win->extra)->type;
	if (type == MANDELBROT)
		return ("mandelbrot");
	else if (type == JULIA)
		return ("julia");
	else
		return ("burning ship");
}

void				put_infos(t_mlx_context *ctx, t_window *win)
{
	char			*frac_name;
	char			*iter;

	frac_name = get_fractal_name(win);
	mlx_string_put(ctx->mlx, ctx->win, ctx->width - (ft_strlen(frac_name) * 10)
			- 2, 0, 0x0066AAAA, frac_name);
	iter = ft_itoa(((t_fractal *)win->extra)->iter);
	iter = ft_strjoinf2("iterations: ", &iter);
	mlx_string_put(ctx->mlx, ctx->win, ctx->width - (ft_strlen(iter) * 10) - 2,
			18, 0x0066AAAA, iter);
	free(iter);
	mlx_string_put(ctx->mlx, ctx->win, 0, 0, 0x00FFFFFF, "Use ");
	mlx_string_put(ctx->mlx, ctx->win, 40, 0, 0x00CC9900, "Arrows");
	mlx_string_put(ctx->mlx, ctx->win, 100, 0, 0x00FFFFFF, " to move around");
	mlx_string_put(ctx->mlx, ctx->win, 0, 18, 0x00FFFFFF, "Use ");
	mlx_string_put(ctx->mlx, ctx->win, 40, 18, 0x00CC9900, "Mouse Wheel or "
			"+/-");
	mlx_string_put(ctx->mlx, ctx->win, 220, 18, 0x00FFFFFF, " to zoom");
	mlx_string_put(ctx->mlx, ctx->win, 0, 36, 0x00FFFFFF, "Press ");
	mlx_string_put(ctx->mlx, ctx->win, 60, 36, 0x00CC9900, "ESC");
	mlx_string_put(ctx->mlx, ctx->win, 90, 36, 0x00FFFFFF, " to quit");
	mlx_string_put(ctx->mlx, ctx->win, 0, 54, 0x00FFFFFF, "Press ");
	mlx_string_put(ctx->mlx, ctx->win, 60, 54, 0x00CC9900, "[ or ]");
	mlx_string_put(ctx->mlx, ctx->win, 120, 54, 0x00FFFFFF, " to change "
			"iteration level");
}
