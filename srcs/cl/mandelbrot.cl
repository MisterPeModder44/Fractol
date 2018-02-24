/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.cl                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 11:05:51 by yguaye            #+#    #+#             */
/*   Updated: 2018/02/16 07:52:35 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frac_mem.h"

#define ABS(x) (x < 0 ? -x : x)

static void			frac_mandel(global t_jfrac *data, global t_cpx *tab,
		global t_clfloat *iter)
{
	private size_t	pos;
	private float	tmp;
	private t_cpx	point;
	private float	i;

	pos = get_global_id(0);
	iter[pos] = 0;
	point.re = .0f;
	point.im = .0f;
	i = 0;
	while (point.re * point.re + point.im * point.im < 4 && i < data->max_iter)
	{
		tmp = point.re * point.re - point.im * point.im + tab[pos].re;
		point.im = ABS(2 * point.re * point.im + tab[pos].im);
		point.re = ABS(tmp);
		++i;
	}
	iter[pos] = i / data->max_iter;
}

static void			frac_julia(global t_jfrac *data, global t_cpx *tab,
		global t_clfloat *iter)
{
	private size_t	pos;
	private float	tmp;
	private t_cpx	point;
	private float	i;

	pos = get_global_id(0);
	iter[pos] = 0;
	//point = tab[pos];
	point = (t_cpx){.re = 0, .im = 0};
	i = 0;
	while (point.re * point.re + point.im * point.im < 4 && i < 10000)
	{
		tmp = point.re * point.re - point.im * point.im + .0;
		point.im = 2 * point.re * point.im + data->c.im - .8;
		point.re = tmp;
		++i;
	}
	iter[pos] = i / 10000;
}


/*
   static void			frac_julia(global t_jfrac *data, global t_cpx *tab,
   global t_clfloat *iter)
   {
   private size_t	pos;
   private float	tmp;
   private t_cpx	point;
   private float	i;
   private float	im;
   private float	re;

   pos = get_global_id(0);
   iter[pos] = 0;
   re = 800.;
   im = 450.;
   i = 0;
   while (re * re + im * im < 4 && i < 200)
   {
   tmp = re * re - im * im + 800.;
   point.im = 2 * re * im + 450.;
   point.re = tmp;
   ++i;
   }
   iter[pos] = i / 200.;
   }*/

kernel void			mandelbrot(global t_jfrac *data, global t_cpx *tab,
		global t_clfloat *iter)
{
	if (data->type == MANDELBROT)
		frac_mandel(data, tab, iter);
	else if (data->type == JULIA)
		frac_mandel(data, tab, iter);
	/*else
	  iter[get_global_id(0)] = .0;*/
}
