/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 16:31:16 by yguaye            #+#    #+#             */
/*   Updated: 2018/01/31 18:05:23 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "fractol.h"
#include "clbin.h"
#include "events.h"

void			load_opencl(t_opencl_ctx *ctx)
{
	init_opencl(ctx, CL_NUM_RUNS);
	load_cl_program(ctx, CL_BIN(CL_JULIA), CL_JULIA_ID);
	load_kernel(ctx, CL_JULIA, CL_JULIA_ID);
	init_kargs(R_ARG(ctx, CL_JULIA_ID), 1, CL_FALSE);
	add_karg(R_ARG(ctx, CL_JULIA_ID),
			NULL, sizeof(cl_float2) * W_PIXELS, ctx->context);
	set_ret_karg(R_ARG(ctx, CL_JULIA_ID), sizeof(cl_int) * W_PIXELS,
			ctx->context);
}

void			init_window(t_mlx_context *ctx)
{
	ctx->mlx = mlx_init();
	ctx->width = W_WIDTH;
	ctx->height = W_HEIGHT;
	ctx->mouse_x = .5;
	ctx->mouse_y = .5;
	add_window(ctx, init_w(ctx, new_window(0, 0, ctx->width, ctx->height)));
	ctx->win = mlx_new_window(ctx->mlx, ctx->width, ctx->height,
			"- Fractol -");
	mlx_key_hook(ctx->win, (int (*)())&on_key_released, ctx);
	mlx_hook(ctx->win, X11_DESTROYNOTIFY, X11_STRUCTURENOTIFYMASK,
			(int (*)())&on_close_window, ctx);
	mlx_hook(ctx->win, X11_MOTIONNOTIFY, 0,
			(int (*)())&on_mouse_movement, ctx);
}
