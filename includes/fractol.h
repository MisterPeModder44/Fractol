/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 08:20:17 by yguaye            #+#    #+#             */
/*   Updated: 2018/01/20 16:52:00 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdint.h>
# include <libft_base/list.h>
# include <libft_math/vectors.h>

typedef enum		e_bool
{
	FALSE = 0,
	TRUE = 1,
}					t_bool;

typedef struct		s_palette
{
	uint8_t			*reds;
	uint8_t			*greens;
	uint8_t			*blues;
	uint32_t		size;
	uint32_t		max_hue;
}					t_palette;

typedef struct		s_mlx_context
{
	void			*mlx;
	void			*win;
	uint32_t		width;
	uint32_t		height;
	void			*img;
	t_palette		*palette;
}					t_mlx_context;

typedef enum		e_interpolation
{
	LINEAR = 1,
}					t_interpolation;

typedef struct		s_color_point
{
	uint8_t			r;
	uint8_t			g;
	uint8_t			b;
	t_interpolation	type;
	uint32_t		pos;
}					t_color_point;

void				put_fractol_render(t_mlx_context *ctx);
void				quit_fractol(t_mlx_context *ctx, const char *reason);

t_bool				get_size(char **tab, size_t len, uint32_t *nums);
t_list				*get_color_point(const char *format);
void				ignore_ws(int *i, const char *str);

t_palette			*parse_palette(const char *format);
t_palette			*new_palette(uint8_t *color1, uint8_t *color2,
		uint32_t size);
void				del_palette(t_palette **palette);

#endif
