/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.cl                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 11:05:51 by yguaye            #+#    #+#             */
/*   Updated: 2018/04/09 16:42:12 by yguaye           ###   ########.fr       */
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
	point.re = tab[pos].re;
	point.im = tab[pos].im;
	i = 0;
	while (point.re * point.re + point.im * point.im < 4 && i < data->max_iter)
	{
		tmp = point.re * point.re - point.im * point.im + data->c.re;
		point.im = 2 * point.re * point.im + data->c.im;
		point.re = tmp;
		++i;
	}
	iter[pos] = i / data->max_iter;
}

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
