/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 08:20:17 by yguaye            #+#    #+#             */
/*   Updated: 2018/01/18 08:31:26 by yguaye           ###   ########.fr       */
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

typedef struct		s_mlx_context
{
	void			*mlx;
	void			*win;
	uint32_t		width;
	uint32_t		height;
	void			*img;
}					t_mlx_context;

void				put_fractol_render(t_mlx_context *ctx);
void				quit_fractol(t_mlx_context *ctx, const char *reason);

#endif
