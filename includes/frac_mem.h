/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frac_mem.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 17:13:33 by yguaye            #+#    #+#             */
/*   Updated: 2018/02/06 13:06:22 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRAC_MEM_H
# define FRAC_MEM_H

# include "ft_opencl_types.h"

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
}				t_jfrac;

#endif
