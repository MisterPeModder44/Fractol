/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandel_julia.cl                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 11:05:51 by yguaye            #+#    #+#             */
/*   Updated: 2018/02/08 11:13:25 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frac_mem.h"

kernel void			mandel_julia(global t_jfrac *data, global t_cpx *tab,
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
