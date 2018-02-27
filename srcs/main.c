/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 08:32:01 by yguaye            #+#    #+#             */
/*   Updated: 2018/02/27 16:15:26 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "fractol.h"

int				main(int ac, char **av)
{
	t_mlx_context	ctx;
	t_opencl_ctx	cl_ctx;
	t_fractal		frac;
	t_args			*args;

	init_mlx_context(&ctx, &cl_ctx);
	args = add_fractol_args(&ctx);
	if (parse_args(args, ac, av) && has_arg_errors(args, ARG_EMPTY))
		quit_arg_error(&args, &ctx);
	read_args(&args, &ctx, &frac);
	init_window(&ctx);
	free_args(&args);
	init_frac_struct(&ctx, &frac);
	win_add_extra_data(ctx.windows->content, &frac, NULL);
	draw_window(ctx.windows->content, &ctx,
			(void (*)(t_window *, void *))frac.draw);
	mlx_loop(ctx.mlx);
	return (0);
}
