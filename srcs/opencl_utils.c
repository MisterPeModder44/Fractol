/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 16:24:16 by yguaye            #+#    #+#             */
/*   Updated: 2018/01/31 16:25:48 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ft_opencl.h"

void				release(void *obj, void (*del)(void *))
{
	if (obj)
		(*del)(obj);
}

static void			shutdown_opencl(t_opencl_ctx *ctx)
{
	release(ctx->kernel, (void (*)(void *))clReleaseKernel);
	release(ctx->program, (void (*)(void *))clReleaseProgram);
	release(ctx->cmd_queue, (void (*)(void *))clReleaseCommandQueue);
	release(ctx->context, (void (*)(void *))clReleaseContext);
}

void				check_status(t_opencl_ctx *ctx, char *msg, cl_int ret)
{
	if (ret != CL_SUCCESS)
	{
		printf("fatal: %s. Error: %d\n", msg, ret);
		shutdown_opencl(ctx);
		exit(-1);
	}
}

void				init_opencl(t_opencl_ctx *ctx)
{
	cl_int			ret;

	clGetPlatformIDs(1, &ctx->platform, NULL);
	ret = clGetDeviceIDs(ctx->platform, CL_GPU, 1, &ctx->device, NULL);
	check_status(ctx, "no GPUs found", ret);
	ctx->context = clCreateContext(NULL, 1, &ctx->device, NULL, NULL, &ret);
	check_status(ctx, "couldn't create openCL context", ret);
	ctx->cmd_queue = clCreateCommandQueue(ctx->context, ctx->device, 0, &ret);
	check_status(ctx, "counldn't create openCL command queue", ret);
	ctx->kernel = NULL;
	ctx->program = NULL;
}
