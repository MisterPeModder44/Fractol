/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.cl                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 11:05:51 by yguaye            #+#    #+#             */
/*   Updated: 2018/03/02 09:50:29 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frac_mem.h"

static void			frac_burning(global t_jfrac *data, global t_cpx *tab,
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
		point.im = FT_ABS(2 * point.re * point.im + tab[pos].im);
		point.re = FT_ABS(tmp);
		++i;
	}
	iter[pos] = i / data->max_iter;
}


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
		point.im = 2 * point.re * point.im + tab[pos].im;
		point.re = tmp;
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
	point = tab[pos];
	i = 0;
	while (point.re * point.re + point.im * point.im < 4 && i < data->max_iter)
	{
		tmp = point.re * point.re - point.im * point.im;
		point.im = 2 * point.re * point.im + 500;
		point.re = tmp + 500;
		++i;
	}
	iter[pos] = i / data->max_iter * 10;
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
		frac_julia(data, tab, iter);
	else if (data->type == BURNING_SHIP)
		frac_burning(data, tab, iter);
	else
		iter[get_global_id(0)] = .0;
}
