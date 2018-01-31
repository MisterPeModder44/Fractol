/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   krun.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 16:16:02 by yguaye            #+#    #+#             */
/*   Updated: 2018/01/31 17:49:18 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft_base/stringft.h>
#include "ft_opencl.h"

void			load_cl_program(t_opencl_ctx *ctx, const char *path,
		size_t id)
{
	size_t				len;
	cl_int				ret;

	len = ft_strlen(path);
	R_PRG(ctx, id) = clCreateProgramWithBinary(ctx->context, 1, &ctx->device,
			&len, (const unsigned char **)&path, NULL, &ret);
	check_status(ctx, "couldn't load program", ret);
	ret = clBuildProgram(R_PRG(ctx, id), 1, &ctx->device, CLC_FLAG, NULL, NULL);
	check_status(ctx, "couldn't build program", ret);
}

void			load_kernel(t_opencl_ctx *ctx,
		const char *name, size_t id)
{
	cl_int				ret;

	R_KRN(ctx, id) = clCreateKernel(R_PRG(ctx, id), name, &ret);
	check_status(ctx, "couldn't load kernel", ret);
}

void			*run_kernel(cl_kernel kernel, t_kargs *args,
		cl_command_queue queue, size_t global)
{
	size_t			i;
	cl_int			r;
	size_t			mem_size;

	if (!args->ret || args->ret->size == 0 || !args->argv)
		return (NULL);
	i = 0;
	r = 0;
	mem_size = sizeof(cl_mem);
	while (i < args->argc)
	{
		r |= clSetKernelArg(kernel, i, sizeof(cl_mem), &args->argv[i].kern_mem);
		++i;
	}
	if ((r |= clSetKernelArg(kernel, i, mem_size, &args->ret->kern_mem))
			!= CL_SUCCESS)
		return (NULL);
	if (clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &global, NULL, 0, NULL,
				NULL) != CL_SUCCESS || clEnqueueReadBuffer(queue,
					args->ret->kern_mem, CL_TRUE, 0, args->ret->size,
					args->ret->host_mem, 0, NULL, NULL))
		return (NULL);
	return (args->ret->host_mem);
}
