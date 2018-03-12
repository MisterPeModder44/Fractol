/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frac_mem.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 17:13:33 by yguaye            #+#    #+#             */
/*   Updated: 2018/03/02 09:05:16 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRAC_MEM_H
# define FRAC_MEM_H

# include "ft_opencl_types.h"

# define FT_ABS(x) (x < 0 ? -x : x)

typedef enum	e_fractype
{
	MANDELBROT = 0,
	JULIA,
	BURNING_SHIP,
	INVALID,
}				t_fractype;

typedef struct	s_jfrac
{
	t_fractype	type;
	size_t		size;
	t_clfloat	max_iter;
	t_cpx		c;
}				t_jfrac;

#endif
