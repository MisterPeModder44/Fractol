/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal_opencl_types_c.h                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 14:17:36 by yguaye            #+#    #+#             */
/*   Updated: 2018/02/08 14:22:26 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERNAL_OPENCL_TYPES_C_H
# define INTERNAL_OPENCL_TYPES_C_H

# ifdef __APPLE__
#  include <OpenCL/opencl.h>
# else
#  include <CL/cl.h>
# endif

typedef cl_char			t_clchar;
typedef cl_uchar		t_cluchar;
typedef cl_int			t_clint;
typedef cl_uint			t_cluint;
typedef cl_long			t_cllong;
typedef cl_ulong		t_clulong;
typedef cl_float		t_clfloat;

#endif
