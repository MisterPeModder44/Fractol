/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 16:24:16 by yguaye            #+#    #+#             */
/*   Updated: 2018/02/08 15:36:01 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void				release(void *obj, void (*del)(void *))
{
	if (obj)
		(*del)(obj);
}

void				shutdown_opencl(t_opencl_ctx *ctx)
{
	size_t			i;

	release(ctx->cmd_queue, (void (*)(void *))clReleaseCommandQueue);
	release(ctx->context, (void (*)(void *))clReleaseContext);
	if (ctx->runs)
	{
		i = 0;
		while (i < ctx->num_runs)
		{
			release(R_PRG(ctx, i), (void (*)(void *))clReleaseProgram);
			release(R_KRN(ctx, i), (void (*)(void *))clReleaseKernel);
			del_kargs(R_ARG(ctx, i));
			release(R_ARG(ctx, i), &free);
			++i;
		}
		free(ctx->runs);
	}
}

void				check_status(t_opencl_ctx *ctx, char *msg, cl_int ret)
{
	if (ret != CL_SUCCESS)
	{
		shutdown_opencl(ctx);
		quit_fractol(NULL, msg);
	}
}

t_bool				init_runnables(t_opencl_ctx *ctx, size_t num)
{
	size_t			i;

	ctx->num_runs = num;
	i = 0;
	while (i < num)
	{
		R_PRG(ctx, i) = NULL;
		R_KRN(ctx, i) = NULL;
		if (!((R_ARG(ctx, i) = (t_kargs *)malloc(sizeof(t_kargs)))))
		{
			while (i > 0)
			{
				free(ctx->runs[i - 1].args);
				--i;
			}
			return (FALSE);
		}
		++i;
	}
	return (TRUE);
}

void				init_opencl(t_opencl_ctx *ctx, size_t num)
{
	cl_int			ret;

	clGetPlatformIDs(1, &ctx->platform, NULL);
	ret = clGetDeviceIDs(ctx->platform, CL_GPU, 1, &ctx->device, NULL);
	check_status(ctx, "no GPUs found", ret);
	ctx->context = clCreateContext(NULL, 1, &ctx->device, NULL, NULL, &ret);
	check_status(ctx, "couldn't create OpenCL context", ret);
	ctx->cmd_queue = clCreateCommandQueue(ctx->context, ctx->device, 0, &ret);
	check_status(ctx, "counldn't create OpenCL command queue", ret);
	if (!num || !(ctx->runs = (t_runnable *)malloc(sizeof(t_runnable) *
					num)) || !init_runnables(ctx, num))
		check_status(ctx, "can't init runnables!", !CL_SUCCESS);
}
