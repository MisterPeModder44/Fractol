/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 08:32:01 by yguaye            #+#    #+#             */
/*   Updated: 2018/02/08 13:45:53 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdlib.h>
#include <libft_base/io.h>
#include "fractol.h"

static void		del_window_lst(t_mlx_context *ctx)
{
	t_list		*curr;
	t_list		*tmp;
	t_window	*win;

	curr = ctx->windows;
	while (curr)
	{
		win = curr->content;
		if (win->img && win->img->img_ptr)
			mlx_destroy_image(ctx->mlx, win->img->img_ptr);
		free(win->img);
		if (win->extra && win->del_extra)
			(*win->del_extra)(win->extra);
		free(win);
		tmp = curr->next;
		free(curr);
		curr = tmp;
	}
	ctx->windows = NULL;
}

void			quit_fractol(t_mlx_context *ctx, const char *reason)
{
	if (ctx)
	{
		if (ctx->windows)
			del_window_lst(ctx);
		if (ctx->palette)
			del_palette(&ctx->palette);
		if (ctx->cl_ctx)
			shutdown_opencl(ctx->cl_ctx);
		mlx_destroy_window(ctx->mlx, ctx->win);
	}
	if (reason)
		ft_putendl_fd(reason, 2);
	exit(reason != NULL);
}

int				main(int ac, char **av)
{
	t_mlx_context	ctx;
	t_opencl_ctx	cl_ctx;
	t_fractal		mandelbrot;

	ctx.cl_ctx = &cl_ctx;
	load_opencl(&cl_ctx);
	if (ac != 2)
		quit_fractol(NULL, "fractol: wrong number of arguments!");
	if (!(ctx.palette = parse_palette(av[1])))
		quit_fractol(NULL, "fractol: couldn't create palette");
	init_window(&ctx);
	mandelbrot.draw = &draw_fractal;
	mandelbrot.palette = ctx.palette;
	mandelbrot.x_max = ctx.width;
	mandelbrot.y_max = ctx.height;
	mandelbrot.x_min = 0;
	mandelbrot.y_min = 0;
	win_add_extra_data(ctx.windows->content, &mandelbrot, NULL);
	draw_window(ctx.windows->content, &ctx,
			(void (*)(t_window *, void *))mandelbrot.draw);
	mlx_loop(ctx.mlx);
	return (0);
}
