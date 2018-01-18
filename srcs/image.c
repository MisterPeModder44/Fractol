/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 08:22:05 by yguaye            #+#    #+#             */
/*   Updated: 2018/01/18 11:14:44 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <libft_math/complex.h>
#include <stdio.h>
#include "image.h"

static void			get_gradient(t_image *img, t_color *color, int i)
{
	int				c;

	c = i % 5;
	if (i == 0 || i == 1000)
		set_color(img, color, (int8_t[3]){0, 0, 0});
	else if (c == 0)
		set_color(img, color, (int8_t[3]){138, 41, 70});
	else if (c == 1)
		set_color(img, color, (int8_t[3]){102, 41, 70});
	else if (c == 2)
		set_color(img, color, (int8_t[3]){182, 158, 99});
	else if (c == 3)
		set_color(img, color, (int8_t[3]){71, 227, 205});
	else if (c == 4)
		set_color(img, color, (int8_t[3]){188, 168, 139});
}

static void			mandelbrot_pixel(t_image *img, t_cpx *point, t_color *color)
{
	double			x;
	double			y;
	int				i;
	double			tmp;

	x = .0;
	y = .0;
	i = 0;
	while (x * x + y * y < 4 && i < 1000)
	{
		tmp = x * x - y * y + point->re;
		y = 2 * x * y + point->im;
		x = tmp;
		++i;
	}
	get_gradient(img, color, i);
}

static void			draw_frac(t_image *img)
{
	t_cpx			point;
	double			y;
	double			x;
	double			dim[2];
	t_color			color;

	y = .0;
	dim[0] = (double)img->ctx->width;
	dim[1] = (double)img->ctx->height;
	while (y < dim[1])
	{
		x = .0;
		while (x < dim[0])
		{
			point = (t_cpx){.re = (3.5 * x) / dim[0] - 2.5, .im = (2 * y) / dim[1] - 1};
			mandelbrot_pixel(img, &point, &color);
			img_pixel_put(img, x, y, &color);
			++x;
		}
		++y;
	}
}

void				put_fractol_render(t_mlx_context *ctx)
{
	t_image			img;

	if (ctx->img)
		mlx_destroy_image(ctx->mlx, ctx->img);
	ctx->img = mlx_new_image(ctx->mlx, ctx->width, ctx->height);
	img.ctx = ctx;
	img.data = mlx_get_data_addr(ctx->img, &img.bpp, &img.slen, &img.endian);
	if (img.bpp < 32)
		quit_fractol(ctx, "fractol: unsupported image format.");
	draw_frac(&img);
	mlx_put_image_to_window(ctx->mlx, ctx->win, ctx->img, 0, 0);
}

void				img_pixel_put(t_image *img, const int x, const int y,
		const t_color *color)
{
	int				pos;

	if (x < 0 || y < 0 ||
			(uint32_t)x >= img->ctx->width || (uint32_t)y >= img->ctx->height)
		return ;
	pos = (x + y * img->ctx->width) * img->bpp / 8;
	img->data[pos] = color->bytes[0];
	img->data[pos + 1] = color->bytes[1];
	img->data[pos + 2] = color->bytes[2];
	img->data[pos + 3] = color->bytes[3];
}
