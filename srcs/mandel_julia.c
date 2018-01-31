/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandel_julia.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 18:08:05 by yguaye            #+#    #+#             */
/*   Updated: 2018/01/31 18:28:37 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void				julia_mandelbrot(t_cpx c, t_opencl_ctx *ctx)
{
	//TODO <to be contined...>
	/*
	   size_t			i;

	   i = 0;
	   while (i < W_PIXELS)
	   {
	   R_ARG()
	   }

	   run_kernel(ctx.kernel, &args, ctx.cmd_queue, NUM_ELEM);*/
}

/*
   void			julia_mandelbrot(t_image *img, t_cpx *point, t_color *color,
   t_palette *pal)
   {
   float			x;
   float			y;
   int				i;
   float			tmp;

   x = .0;
   y = .0;
   i = 0;
   while (x * x + y * y < 4 && i < MAX_ITER)
   {
   tmp = x * x - y * y + point->re;
   y = 2 * x * y + point->im;
   x = tmp;
   ++i;
   }
   if (i == 1000)
 *color = set_color(img, 0, 0, 0);
 else
 *color = get_gradient(img, pal, (float)i / MAX_ITER);
 }
 */
