/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 16:31:16 by yguaye            #+#    #+#             */
/*   Updated: 2018/04/10 12:46:21 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "fractol.h"
#include "clbin.h"
#include "events.h"
#include <libft_base/io.h>
#include <libft_base/memory.h>

void			load_opencl(t_opencl_ctx *ctx)
{
	size_t		size;

	size = W_PIXELS;
	init_opencl(ctx, CL_NUM_RUNS);
	init_kargs(R_ARG(ctx, CL_MANDEL_ID), 2, CL_FALSE);
	load_cl_program(ctx, CL_BIN(CL_MANDEL), CL_MANDEL_ID);
	load_kernel(ctx, CL_MANDEL, CL_MANDEL_ID);
	add_karg(R_ARG(ctx, CL_MANDEL_ID), sizeof(t_jfrac), ctx->context);
	add_karg(R_ARG(ctx, CL_MANDEL_ID), sizeof(t_cpx) * size, ctx->context);
	set_ret_karg(R_ARG(ctx, CL_MANDEL_ID), sizeof(t_clfloat) * size,
			ctx->context);
}

void			init_mlx_context(t_mlx_context *ctx, t_opencl_ctx *ocl)
{
	ft_bzero(ctx, sizeof(t_mlx_context));
	load_opencl(ocl);
	ctx->cl_ctx = ocl;
	ctx->width = W_WIDTH;
	ctx->height = W_HEIGHT;
	ctx->mouse_ax = .5;
	ctx->mouse_ay = .5;
	ctx->mouse_px = ctx->width / 2;
	ctx->mouse_py = ctx->height / 2;
	ctx->mouse_lx = .5;
	ctx->mouse_ly = .5;
	ctx->locked = 0;
}

void			init_window(t_mlx_context *ctx)
{
	ctx->mlx = mlx_init();
	add_window(ctx, init_w(ctx, new_window(0, 0, ctx->width, ctx->height)));
	ctx->win = mlx_new_window(ctx->mlx, ctx->width, ctx->height,
			"- Fractol -");
	mlx_key_hook(ctx->win, (int (*)())&on_key_released, ctx);
	mlx_mouse_hook(ctx->win, (int (*)())&on_mouse_pressed, ctx);
	mlx_hook(ctx->win, X11_DESTROYNOTIFY, X11_STRUCTURENOTIFYMASK,
			(int (*)())&on_close_window, ctx);
	mlx_hook(ctx->win, X11_MOTIONNOTIFY, 0,
			(int (*)())&on_mouse_movement, ctx);
}

t_args			*add_fractol_args(t_mlx_context *ctx)
{
	t_args		*args;

	args = init_args(ARG_MSIMPLE | ARG_MSINGLE_PARAMS, NULL, "usage: fractol "
			"<-fractal ...> [<-palette \"my palette\"> | <-preset ...>] "
			"[-iter <number>]\n"
			"valid presets: gold, spectre, blackAndWhite\n"
			"valid fractals: mandelbrot, julia, burning");
	if (!args || add_arg_param(args, "palette", 1, SIZEP_FORCE) ||
			add_arg_param(args, "preset", 1, SIZEP_FORCE) ||
			add_arg_param(args, "help", 0, SIZEP_FORCE) ||
			add_arg_param(args, "iter", 1, SIZEP_FORCE) ||
			add_arg_param(args, "fractal", 1, SIZEP_FORCE))
		quit_arg_error(args ? &args : NULL, ctx);
	return (args);
}

void			init_frac_struct(t_mlx_context *ctx, t_fractal *frac)
{
	frac->draw = &draw_fractal;
	frac->palette = ctx->palette;
	frac->x_max = ctx->width;
	frac->y_max = ctx->height;
	frac->x_min = 0;
	frac->y_min = 0;
}
