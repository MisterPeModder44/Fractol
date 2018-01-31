/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kargs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 10:02:54 by yguaye            #+#    #+#             */
/*   Updated: 2018/01/31 17:51:06 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft_base/memory.h>
#include <stdio.h>
#include "ft_opencl.h"

void					init_kargs(t_kargs *args, size_t argc, cl_bool reset)
{
	size_t				i;

	if (reset == CL_TRUE)
		del_kargs(args);
	args->argc = argc;
	if (argc == 0 || !(args->argv = (t_karg *)malloc(sizeof(t_karg) * argc)))
	{
		args->argv = NULL;
		return ;
	}
	i = 0;
	while (i < args->argc)
	{
		args->argv[i].host_mem = NULL;
		args->argv[i].kern_mem = NULL;
		++i;
	}
	args->curr = 0;
	args->ret = NULL;
}

void					add_karg(t_kargs *args, void *arg, size_t size,
		cl_context ctx)
{
	cl_int				ret;
	t_karg				a;

	if (!args->argv)
		return ;
	a = args->argv[args->curr];
	if ((args->argv[args->curr].host_mem = malloc(size)))
	{
		if (arg)
			ft_memmove(args->argv[args->curr].host_mem, arg, size);
		else
			ft_bzero(args->argv[args->curr].host_mem, size);
		if ((args->argv[args->curr].kern_mem = clCreateBuffer(ctx,
						CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, size,
						args->argv[args->curr].host_mem, &ret))
				&& ret == CL_SUCCESS)
		{
			args->argv[args->curr].size = size;
			++args->curr;
			return ;
		}
	}
	args->argv[args->curr].host_mem = NULL;
	args->argv[args->curr].kern_mem = NULL;
	del_kargs(args);
}

void					set_ret_karg(t_kargs *args, size_t siz, cl_context ctx)
{
	cl_int				r;

	if (args->ret && args->ret->size == siz)
	{
		ft_bzero(args->ret->host_mem, siz);
		return ;
	}
	else if (args->ret)
	{
		free(args->ret->host_mem);
		clReleaseMemObject(args->ret->kern_mem);
	}
	else if (!(args->ret = (t_karg *)malloc(sizeof(t_karg))))
		return ;
	args->ret->size = 0;
	args->ret->kern_mem = clCreateBuffer(ctx, CL_MEM_WRITE_ONLY, siz, NULL, &r);
	if (!(args->ret->host_mem = malloc(siz)) || r != CL_SUCCESS)
		return ;
	ft_bzero(args->ret->host_mem, siz);
	args->ret->size = siz;
}

void					del_kargs(t_kargs *args)
{
	size_t				i;
	t_karg				arg;

	if (args->argv)
	{
		i = 0;
		while (i < args->argc)
		{
			arg = args->argv[i];
			if (arg.host_mem)
				free(arg.host_mem);
			if (arg.kern_mem)
				clReleaseMemObject(arg.kern_mem);
			++i;
		}
		free(args->argv);
		args->argv = NULL;
	}
	if (args->ret)
	{
		if (args->ret->host_mem)
			free(args->ret->host_mem);
		if (args->ret->kern_mem)
			clReleaseMemObject(args->ret->kern_mem);
	}
}
