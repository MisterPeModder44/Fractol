/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandel_julia.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 18:08:05 by yguaye            #+#    #+#             */
/*   Updated: 2018/02/08 14:33:50 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft_base/memory.h>
#include "clbin.h"
#include "fractol.h"
#include "frac_mem.h"

t_jfrac				*init_frac_mem(t_jfrac *frac, t_fractype type,
		size_t pixels, t_clint max_iter)
{
	if (type >= INVALID)
		return (NULL);
	frac->type = type;
	frac->size = pixels;
	frac->max_iter = (t_clfloat)max_iter;
	return (frac);
}

t_bool				set_frac_mem(t_opencl_ctx *ctx, t_jfrac *frac, t_cpx *tab)
{
	t_kargs			*args;
	t_karg			*ret;
	size_t			s;

	args = R_ARG(ctx, CL_JULIA_ID);
	ret = args->ret;
	s = frac->size;
	ft_bzero(ret->host_mem, ret->size);
	if ((
				clEnqueueWriteBuffer(ctx->cmd_queue, args->argv[0].kern_mem,
					CL_TRUE, 0, sizeof(t_jfrac), frac, 0, NULL, NULL)
				| clEnqueueWriteBuffer(ctx->cmd_queue, args->argv[1].kern_mem,
					CL_TRUE, 0, sizeof(t_cpx) * s, tab, 0, NULL, NULL)
				| clEnqueueWriteBuffer(ctx->cmd_queue, ret->kern_mem,
					CL_TRUE, 0, ret->size, ret->host_mem, 0, NULL, NULL))
			!= CL_SUCCESS)
	{
		free(tab);
		return (FALSE);
	}
	free(tab);
	return (TRUE);
}
