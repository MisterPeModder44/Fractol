/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 10:51:31 by yguaye            #+#    #+#             */
/*   Updated: 2018/01/18 18:59:35 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENTS_H
# define EVENTS_H

# include "fractol.h"

# define X11_STRUCTURENOTIFYMASK (1L << 17)
# define X11_DESTROYNOTIFY 17

# define ESC_KEY 53

int				on_key_released(int key, t_mlx_context *ctx);
int				on_close_window(t_mlx_context *ctx);

#endif
