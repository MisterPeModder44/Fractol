/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 14:50:54 by yguaye            #+#    #+#             */
/*   Updated: 2018/02/27 14:53:22 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
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
		if (ctx->mlx && ctx->win)
			mlx_destroy_window(ctx->mlx, ctx->win);
	}
	if (reason && *reason)
		ft_putendl_fd(reason, 2);
	exit(reason != NULL);
}

void			quit_arg_error(t_args **args, t_mlx_context *ctx)
{
	put_arg_error("fractol", args ? *args : NULL);
	if (args)
		free_args(args);
	quit_fractol(ctx, "");
}

void			quit_arg_reason(t_args **args, t_mlx_context *ctx,
		const char *reason)
{
	if (args)
		free_args(args);
	quit_fractol(ctx, reason);
}
