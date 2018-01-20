/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 08:32:01 by yguaye            #+#    #+#             */
/*   Updated: 2018/01/20 15:06:49 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <libft_base/io.h>
#include "fractol.h"
#include "events.h"

void			quit_fractol(t_mlx_context *ctx, const char *reason)
{
	if (ctx)
		mlx_destroy_window(ctx->mlx, ctx->win);
	if (reason)
		ft_putendl_fd(reason, 2);
	if (ctx && ctx->img)
		mlx_destroy_image(ctx->mlx, ctx->img);
	if (ctx && ctx->palette)
		del_palette(&ctx->palette);
	exit(reason != NULL);
}

/*
   static void		init_window(t_mlx_context *ctx)
   {
   ctx->mlx = mlx_init();
   ctx->img = NULL;
   ctx->width = 1600;
   ctx->height = 900;
   if (!(ctx->palette = new_palette((uint8_t[3]){0x62, 0xae, 0xd1}, (uint8_t[3]){0xff, 0xff, 0xff}, 100)))
   quit_fractol(ctx, "couldn't create palette");
   ctx->win = mlx_new_window(ctx->mlx, ctx->width, ctx->height,
   "- Fractol -");
   mlx_key_hook(ctx->win, (int (*)())&on_key_released, ctx);
   mlx_hook(ctx->win, X11_DESTROYNOTIFY, X11_STRUCTURENOTIFYMASK,
   (int (*)())&on_close_window, ctx);
   }*/

int				main(int ac, char **av)
{
	/*
	   t_mlx_context	ctx;

	   init_window(&ctx);
	   put_fractol_render(&ctx);
	   mlx_loop(ctx.mlx);*/
	if (ac == 2)
		parse_palette(av[1]);
	return (0);
}
