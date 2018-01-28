/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 10:51:31 by yguaye            #+#    #+#             */
/*   Updated: 2018/01/28 09:31:51 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENTS_H
# define EVENTS_H

# include "fractol.h"

# define X11_STRUCTURENOTIFYMASK (1L << 17)

# define X11_MOTIONNOTIFY 6
# define X11_DESTROYNOTIFY 17

# define ESC_KEY 53
# define PLUS_KEY 69
# define MINUS_KEY 78

int			on_key_released(int key, t_mlx_context *ctx);
int			on_close_window(t_mlx_context *ctx);
int			on_mouse_movement(int x, int y, t_mlx_context *ctx);

#endif
