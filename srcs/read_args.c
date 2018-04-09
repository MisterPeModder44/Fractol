/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 16:14:58 by yguaye            #+#    #+#             */
/*   Updated: 2018/04/09 18:52:18 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
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
		else if (ft_strequ(str, "spectre"))
			str = "#000000; #555555@5; #E1B941@15; #FFFFFF@100; [100, 1000]";
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

static int		is_integral(char *str)
{
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		++str;
	}
	return (1);
}

static void		get_iter_arg(t_args **args, t_mlx_context *ctx,
		t_fractal *frac)
{
	t_argv_plst	*tmp;

	if ((tmp = get_pargv(*args, "iter")))
	{
		if (!is_integral(*tmp->values))
			quit_arg_reason(args, ctx, ERRSTR "invalid iteration number");
		frac->iter = ft_atoi(*tmp->values);
	}
}

static void		get_fractal_arg(t_args **args, t_mlx_context *ctx,
		t_fractal *frac)
{
	t_argv_plst	*tmp;
	char		*str;

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

void			read_args(t_args **args, t_mlx_context *ctx, t_fractal *frac)
{
	if (has_arg(*args, NULL, DEFAULT))
		quit_arg_reason(args, ctx, ERRSTR "non-parameter arguments are not "
				"valid!");
	if (!has_arg(*args, "fractal", PARAMETER))
		quit_arg_reason(args, ctx, ERRSTR "missing fractal parameter!");
	if (has_arg(*args, "help", PARAMETER))
	{
		show_usage(*args);
		quit_arg_reason(args, ctx, NULL);
	}
	if (has_arg(*args, "iter", PARAMETER))
		get_iter_arg(args, ctx, frac);
	else
		frac->iter = DEFAULT_ITER;
	if (has_arg(*args, "palette", PARAMETER)
			&& has_arg(*args, "preset", PARAMETER))
		quit_arg_reason(args, ctx, ERRSTR "palette and preset parameters "
				"are not compatible!");
	get_palette(args, ctx);
	get_fractal_arg(args, ctx, frac);
}
