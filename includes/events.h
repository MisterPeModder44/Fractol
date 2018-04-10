/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 10:51:31 by yguaye            #+#    #+#             */
/*   Updated: 2018/04/10 12:53:14 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENTS_H
# define EVENTS_H

# include "fractol.h"

# define X11_STRUCTURENOTIFYMASK (1L << 17)

# define X11_MOTIONNOTIFY 6
# define X11_DESTROYNOTIFY 17

# define R_KEY 15
# define ESC_KEY 53
# define PLUS_KEY 69
# define MINUS_KEY 78
# define RBRACKET_KEY 30
# define LBRACKET_KEY 33
# define L_KEY 37

# define SCROLL_UP_KEY 4
# define SCROLL_DOWN_KEY 5

int			on_key_released(int key, t_mlx_context *ctx);
int			on_close_window(t_mlx_context *ctx);
int			on_mouse_movement(int x, int y, t_mlx_context *ctx);
int			on_mouse_pressed(int button, int x, int y, t_mlx_context *ctx);
void		reset_zoom(t_mlx_context *ctx, t_window *win, t_fractal *frac);
void		change_iter_level(t_mlx_context *ctx, t_bool what, t_fractal *frac);

#endif
