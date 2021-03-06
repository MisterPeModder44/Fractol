/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 08:20:17 by yguaye            #+#    #+#             */
/*   Updated: 2018/04/10 12:45:37 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <libft_base/list.h>
# include <libft_args/args.h>
# include "palette.h"
# include "image.h"
# include "ft_opencl.h"
# include "frac_mem.h"

# define DEFAULT_ITER 250

# define W_WIDTH 1600
# define W_HEIGHT 900
# define W_PIXELS W_WIDTH * W_HEIGHT
# define ERRSTR "fractol: \033[1;31merror: \033[0m"

typedef struct		s_mlx_context
{
	t_opencl_ctx	*cl_ctx;
	void			*mlx;
	void			*win;
	uint32_t		width;
	uint32_t		height;
	t_list			*windows;
	t_palette		*palette;
	double			mouse_ax;
	double			mouse_ay;
	double			mouse_px;
	double			mouse_py;
	double			mouse_lx;
	double			mouse_ly;
	int				locked;
}					t_mlx_context;

typedef struct		s_window
{
	int32_t			pos_x;
	int32_t			pos_y;
	uint32_t		width;
	uint32_t		height;
	t_image			*img;
	void			*extra;
	void			(*del_extra)(void *);
	t_mlx_context	*ctx;
}					t_window;

typedef struct		s_fractal
{
	void			(*draw)(t_window *, t_mlx_context *);
	t_palette		*palette;
	double			x_min;
	double			y_min;
	double			x_max;
	double			y_max;
	t_fractype		type;
	int				iter;
}					t_fractal;

void				init_mlx_context(t_mlx_context *ctx, t_opencl_ctx *ocl);

void				init_window(t_mlx_context *ctx);

t_args				*add_fractol_args(t_mlx_context *ctx);

void				init_frac_struct(t_mlx_context *ctx, t_fractal *frac);

void				load_opencl(t_opencl_ctx *ctx);

void				draw_fractal(t_window *win, t_mlx_context *ctx);

t_jfrac				*init_frac_mem(t_jfrac *frac, t_fractype type,
		size_t pixels, t_clint max_iter);

t_bool				set_frac_mem(t_opencl_ctx *ctx, t_jfrac *frac, t_cpx *tab,
		t_cpx c);
void				quit_fractol(t_mlx_context *ctx, const char *reason);

void				quit_arg_error(t_args **args, t_mlx_context *ctx);

void				quit_arg_reason(t_args **args, t_mlx_context *ctx,
		const char *reason);

t_window			*new_window(int32_t x, int32_t y, uint32_t w, uint32_t h);

t_window			*init_w(t_mlx_context *ctx, t_window *win);

void				win_add_extra_data(t_window *win, void *dat,
		void (*f)(void *));

void				draw_window(t_window *win, void *extra,
		void (*draw)(t_window *, void *));

void				draw_fwindow(t_list *win);

void				win_pixel_put(t_window *win, int32_t x, int32_t y,
		t_color col);

t_bool				add_window(t_mlx_context *ctx, t_window *win);

double				clamp(double num, double min, double max);

void				read_args(t_args **args, t_mlx_context *ctx,
		t_fractal *frac);

void				put_infos(t_mlx_context *ctx, t_window *win);

#endif
