/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 10:54:10 by yguaye            #+#    #+#             */
/*   Updated: 2018/01/18 10:54:12 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"

int			on_close_window(t_mlx_context *ctx)
{
	quit_fractol(ctx, NULL);
	return (0);
}

int			on_key_released(int key, t_mlx_context *ctx)
{
	if (key == ESC_KEY)
		on_close_window(ctx);
	return (0);
}
