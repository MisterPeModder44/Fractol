/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_opencl_types.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 17:33:24 by yguaye            #+#    #+#             */
/*   Updated: 2018/02/08 15:36:13 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_OPENCL_TYPES_H
# define FT_OPENCL_TYPES_H

# ifdef __ROUNDING_MODE__
#  define IS_OPENCL 1
# else
#  define IS_OPENCL 0
# endif

# if IS_OPENCL == 1
#  include "internal_opencl_types_cl.h"
# else
#  include "internal_opencl_types_c.h"
# endif

typedef struct			s_cpx
{
	t_clfloat			re;
	t_clfloat			im;
}						t_cpx;

#endif
