/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 13:42:48 by yguaye            #+#    #+#             */
/*   Updated: 2018/02/08 17:22:10 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <mlx.h>
#include "fractol.h"

t_window		*new_window(int32_t x, int32_t y, uint32_t w, uint32_t h)
{
	t_window	*win;

	if (!(win = (t_window *)malloc(sizeof(t_window))))
		return (NULL);
	win->pos_x = x;
	win->pos_y = y;
	win->width = w;
	win->height = h;
	win->del_extra = NULL;
	win->extra = NULL;
	if (!(win->img = (t_image *)malloc(sizeof(t_image))))
		return (NULL);
	win->img->img_ptr = NULL;
	win->ctx = NULL;
	return (win);
}

void			win_add_extra_data(t_window *win, void *dat, void (*f)(void *))
{
	if (win->extra && win->del_extra)
	{
		(*win->del_extra)(win->extra);
		win->extra = NULL;
	}
	win->extra = dat;
	win->del_extra = f;
}

void			draw_window(t_window *win, void *extra,
		void (*draw)(t_window *, void *))
{
	t_image		*img;

	img = win->img;
	if (img->img_ptr)
		mlx_destroy_image(win->ctx->mlx, img->img_ptr);
	img->img_ptr = mlx_new_image(win->ctx->mlx, win->width, win->height);
	img->data = mlx_get_data_addr(img->img_ptr, &img->bpp, &img->slen,
			&img->endian);
	if (img->bpp < 32)
		quit_fractol(win->ctx, "fractol: unsupported image format.");
	draw(win, extra);
	mlx_put_image_to_window(win->ctx->mlx, win->ctx->win, img->img_ptr,
			win->pos_x, win->pos_y);
}

void			win_pixel_put(t_window *win, int32_t x, int32_t y, t_color col)
{
	int			pos;

	if (x < 0 || y < 0 ||
			(uint32_t)x >= win->width || (uint32_t)y >= win->height)
		return ;
	pos = (x + y * win->width) * win->img->bpp / 8;
	win->img->data[pos] = col.bytes[0];
	win->img->data[pos + 1] = col.bytes[1];
	win->img->data[pos + 2] = col.bytes[2];
	win->img->data[pos + 3] = col.bytes[3];
}

t_bool			add_window(t_mlx_context *ctx, t_window *win)
{
	t_list		*nl;

	if (!(nl = ft_lstnew(NULL, 0)))
		return (FALSE);
	nl->content_size = sizeof(t_window);
	nl->content = win;
	ft_lstadd(&ctx->windows, nl);
	return (TRUE);
}
