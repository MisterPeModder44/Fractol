/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 08:32:01 by yguaye            #+#    #+#             */
/*   Updated: 2018/02/27 15:51:52 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdlib.h>
#include <libft_base/io.h>
#include <libft_base/stringft.h>
#include "fractol.h"

static void		get_palette(t_args **args, t_mlx_context *ctx)
{
	t_argv_plst	*tmp;
	char		*str;

	if ((tmp = get_pargv(*args, "palette")))
		str = *tmp->values;
	else if ((tmp = get_pargv(*args, "preset")))
	{
		str = *tmp->values;
		if (ft_strequ(str, "gold"))
			str = "#000000; #E1B941@15; #FFFFFF@100; [100, 1000]";
		else if (ft_strequ(str, "blackAndWhite"))
			str = "#000000; #FFFFFF@1; [1,1000]";
		else
			quit_arg_reason(args, ctx, ERRSTR "invalid preset.");
	}
	else
		str = "#000000; #FFFFFF@1; [1,1000]";
	if (!(ctx->palette = parse_palette(str)))
		quit_arg_reason(args, ctx, ERRSTR "couldn't create palette.");
}

static void		read_args(t_args **args, t_mlx_context *ctx, t_fractal *frac)
{
	t_argv_plst	*tmp;
	char		*str;

	if (has_arg(*args, "palette", PARAMETER)
			&& has_arg(*args, "preset", PARAMETER))
		quit_arg_reason(args, ctx, ERRSTR "palette and preset parameters "
				"are not compatible!");
	get_palette(args, ctx);
	if ((tmp = get_pargv(*args, "fractal")))
	{
		str = *tmp->values;
		if (ft_strequ(str, "mandelbrot"))
			frac->type = MANDELBROT;
		else if (ft_strequ(str, "julia"))
			frac->type = JULIA;
		else if (ft_strequ(str, "burning"))
			frac->type = BURNING_SHIP;
		else
			quit_arg_reason(args, ctx, ERRSTR "invalid fractal.");
	}
	else
		frac->type = JULIA;
}

static void		init_frac_struct(t_mlx_context *ctx, t_fractal *frac)
{
	frac->draw = &draw_fractal;
	frac->palette = ctx->palette;
	frac->x_max = ctx->width;
	frac->y_max = ctx->height;
	frac->x_min = 0;
	frac->y_min = 0;
}

int				main(int ac, char **av)
{
	t_mlx_context	ctx;
	t_opencl_ctx	cl_ctx;
	t_fractal		frac;
	t_args			*args;

	init_mlx_context(&ctx, &cl_ctx);
	args = init_args(ARG_MSIMPLE, NULL, "usage: fractol "
			"[<-palette \"my palette\"> | <-preset ...>] [-fractal ...]\n"
			"valid presets: gold, blackAndWhite\n"
			"valid fractals: mandelbrot, julia, burning");
	if (!args || add_arg_param(args, "palette", 1, SIZEP_FORCE) ||
			add_arg_param(args, "preset", 1, SIZEP_FORCE) ||
			add_arg_param(args, "fractal", 1, SIZEP_FORCE))
		quit_arg_error(args ? &args : NULL, &ctx);
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
