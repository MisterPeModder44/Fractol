/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 08:22:05 by yguaye            #+#    #+#             */
/*   Updated: 2018/01/27 13:21:22 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <libft_math/complex.h>
#include <stdio.h>
#include "image.h"

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
	if (i == 1000)
		*color = set_color(img, 0, 0, 0);
	else
		*color = get_gradient(img, img->ctx->palette, (double)i / 1000.0);
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
			point = (t_cpx){.re = (3.5 * x) / dim[0] - 2.5, .im = (2 * y) /
				dim[1] - 1};
			mandelbrot_pixel(img, &point, &color);
			img_pixel_put(img, x, y, color);
			++x;
		}
		++y;
	}
}

static void			put_gradient_bar(t_image *img, t_mlx_context *ctx)
{
	uint32_t		x;
	t_color			black;
	t_color			color;
	uint32_t		y;

	x = 0;
	black = (t_color){.value = 0x00000000};
	while (x < ctx->width)
	{
		y = ctx->height - 20;
		img_pixel_put(img, x, y - 1, black);
		color = get_gradient(img, ctx->palette, (double)x / (double)ctx->width);
		while (y < ctx->height)
		{
			img_pixel_put(img, x, y, color);
			++y;
		}
		++x;
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
	put_gradient_bar(&img, ctx);
	mlx_put_image_to_window(ctx->mlx, ctx->win, ctx->img, 0, 0);
}

void				img_pixel_put(t_image *img, const int x, const int y,
		const t_color color)
{
	int				pos;

	if (x < 0 || y < 0 ||
			(uint32_t)x >= img->ctx->width || (uint32_t)y >= img->ctx->height)
		return ;
	pos = (x + y * img->ctx->width) * img->bpp / 8;
	img->data[pos] = color.bytes[0];
	img->data[pos + 1] = color.bytes[1];
	img->data[pos + 2] = color.bytes[2];
	img->data[pos + 3] = color.bytes[3];
}
