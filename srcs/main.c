/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 08:32:01 by yguaye            #+#    #+#             */
/*   Updated: 2018/02/28 10:44:50 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <signal.h>
#include <libft_base/io.h>
#include "fractol.h"

static void		fractol_signal_handler(int sig)
{
	quit_fractol(NULL, "\b\bfractol: cought interruption signal, exiting...");
	(void)sig;
}

int				main(int ac, char **av)
{
	t_mlx_context	ctx;
	t_opencl_ctx	cl_ctx;
	t_fractal		frac;
	t_args			*args;

	if (signal(SIGINT, &fractol_signal_handler) == SIG_ERR)
		ft_putendl_fd("fractol: \033[1;93mwarning:\033[0m couldn't catch "
				"interuption signal!", 2);
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
