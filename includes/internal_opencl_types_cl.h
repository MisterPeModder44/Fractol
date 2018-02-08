/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal_opencl_types_cl.h                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 14:17:34 by yguaye            #+#    #+#             */
/*   Updated: 2018/02/08 14:19:57 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERNAL_OPENCL_TYPES_CL_H
# define INTERNAL_OPENCL_TYPES_CL_H
# ifdef __ROUNDING_MODE__

typedef bool			t_clbool;
typedef char			t_clchar;
typedef unsigned char	t_cluchar;
typedef int				t_clint;
typedef unsigned int	t_cluint;
typedef long			t_cllong;
typedef unsigned long	t_clulong;
typedef float			t_clfloat;
typedef half			t_clhalf;

# endif
#endif
