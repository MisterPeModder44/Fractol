/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kargs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 10:02:54 by yguaye            #+#    #+#             */
/*   Updated: 2018/03/01 16:59:09 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft_base/memory.h>
#include "fractol.h"

void					init_kargs(t_kargs *args, size_t argc, cl_bool reset)
{
	size_t				i;

	if (reset == CL_TRUE)
		del_kargs(args);
	(args)->argc = argc;
	if (argc == 0 || !((args)->argv = (t_karg *)malloc(sizeof(t_karg) * argc)))
		quit_fractol(NULL, "fractol: couldn't allocate arguments!");
	i = 0;
	while (i < (args)->argc)
	{
		(args)->argv[i].host_mem = NULL;
		(args)->argv[i].kern_mem = NULL;
		++i;
	}
	(args)->curr = 0;
	(args)->ret = NULL;
}

void					add_karg(t_kargs *args, size_t size, cl_context ctx)
{
	cl_int				ret;
	t_karg				a;

	args->argv[args->curr].host_mem = NULL;
	if (!args->argv)
		return ;
	a = args->argv[args->curr];
	if ((args->argv[args->curr].kern_mem = clCreateBuffer(ctx, CL_MEM_READ_ONLY,
					size, NULL, &ret)) && ret == CL_SUCCESS)
	{
		args->argv[args->curr].size = size;
		++args->curr;
		return ;
	}
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
		free(args->ret);
	}
	else if (!(args->ret = (t_karg *)malloc(sizeof(t_karg))))
		return ;
	args->ret->size = 0;
	args->ret->kern_mem = clCreateBuffer(ctx, CL_MEM_WRITE_ONLY, siz, NULL, &r);
	if (!(args->ret->host_mem = ft_memalloc(siz)) || r != CL_SUCCESS)
		return ;
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
			release(arg.host_mem, &free);
			release(arg.kern_mem, (void (*)(void *))&clReleaseMemObject);
			++i;
		}
		free(args->argv);
		args->argv = NULL;
	}
	if (args->ret)
	{
		release(args->ret->host_mem, &free);
		release(args->ret->kern_mem, (void (*)(void *))&clReleaseMemObject);
		free(args->ret);
		args->ret = NULL;
	}
}
