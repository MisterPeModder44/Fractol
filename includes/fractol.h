/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 08:20:17 by yguaye            #+#    #+#             */
/*   Updated: 2018/01/31 18:15:48 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <libft_base/list.h>
# include "palette.h"
# include "image.h"
# include "ft_opencl.h"

# define MAX_ITER 200.

# define W_WIDTH 1600
# define W_HEIGHT 900
# define W_PIXELS W_WIDTH * W_HEIGHT

typedef struct		s_mlx_context
{
	t_opencl_ctx	*cl_ctx;
	void			*mlx;
	void			*win;
	uint32_t		width;
	uint32_t		height;
	t_list			*windows;
	t_palette		*palette;
	double			mouse_x;
	double			mouse_y;
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
	void			(*draw)(t_window *);
	t_palette		*palette;
	double			x_min;
	double			y_min;
	double			x_max;
	double			y_max;
}					t_fractal;

typedef float		t_cpx[2];

void				init_window(t_mlx_context *ctx);

void				load_opencl(t_opencl_ctx *ctx);

void				draw_fractal(t_window *win, t_opencl_ctx *ctx);

void				julia_mandelbrot(t_cpx c, t_opencl_ctx *ctx);

void				quit_fractol(t_mlx_context *ctx, const char *reason);

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

#endif
