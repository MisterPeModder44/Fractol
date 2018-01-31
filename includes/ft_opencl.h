/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_opencl.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/28 11:43:28 by yguaye            #+#    #+#             */
/*   Updated: 2018/01/31 17:47:31 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_OPENCL_H
# define FT_OPENCL_H

# ifdef __APPLE__
#  include <OpenCL/opencl.h>
# else
#  include <CL/cl.h>
# endif

# include <libft_base/list.h>

# define CL_GPU CL_DEVICE_TYPE_GPU
# define CLC_FLAG "-Werror"

# define R_PRG(CTX, ID) (CTX->runs[ID].program)
# define R_KRN(CTX, ID) (CTX->runs[ID].kernel)
# define R_ARG(CTX, ID) (CTX->runs[ID].args)

typedef struct			s_karg
{
	void				*host_mem;
	cl_mem				kern_mem;
	size_t				size;
}						t_karg;

typedef struct			s_kargs
{
	t_karg				*argv;
	t_karg				*ret;
	size_t				argc;
	size_t				curr;
}						t_kargs;

typedef struct			s_runnable
{
	cl_program			program;
	cl_kernel			kernel;
	t_kargs				*args;
}						t_runnable;

typedef struct			s_opencl_ctx
{
	cl_context			context;
	cl_platform_id		platform;
	cl_device_id		device;
	cl_command_queue	cmd_queue;
	t_runnable			*runs;
	size_t				num_runs;
}						t_opencl_ctx;

void					init_opencl(t_opencl_ctx *ctx, size_t runnables);

void					shutdown_opencl(t_opencl_ctx *ctx);

void					release(void *obj, void (*del)(void *));

void					check_status(t_opencl_ctx *ctx, char *msg, cl_int ret);

void					load_cl_program(t_opencl_ctx *ctx, const char *path,
		size_t id);

void					load_kernel(t_opencl_ctx *ctx,
		const char *name, size_t id);

void					*run_kernel(cl_kernel kernel, t_kargs *args,
		cl_command_queue queue, size_t global);

void					init_kargs(t_kargs *args, size_t argc, cl_bool reset);

void					add_karg(t_kargs *args, void *arg, size_t size,
		cl_context ctx);

void					set_ret_karg(t_kargs *args, size_t siz, cl_context ctx);

void					del_kargs(t_kargs *args);

#endif
