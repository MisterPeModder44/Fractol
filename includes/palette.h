/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   palette.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 17:01:52 by yguaye            #+#    #+#             */
/*   Updated: 2018/01/20 17:03:40 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PALETTE_H
# define PALETTE_H

# include <stdint.h>
# include <libft_base/list.h>

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

t_bool				get_size(char **tab, size_t len, uint32_t *nums);
t_list				*get_color_point(const char *format);
void				ignore_ws(int *i, const char *str);

t_palette			*parse_palette(const char *format);
t_palette			*new_palette(uint8_t *color1, uint8_t *color2,
		uint32_t size);
void				del_palette(t_palette **palette);

#endif
