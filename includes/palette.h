/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   palette.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 17:01:52 by yguaye            #+#    #+#             */
/*   Updated: 2018/01/27 13:24:57 by yguaye           ###   ########.fr       */
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

typedef enum		e_interpolation
{
	LINEAR = 1,
}					t_interpolation;

typedef struct		s_color_point
{
	uint8_t			r;
	uint8_t			g;
	uint8_t			b;
	int				type;
	uint32_t		pos;
}					t_color_point;

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
t_bool				val_palette(t_list *colors, uint32_t size, uint32_t mhue);
t_palette			*make_palette(t_list *colors, uint32_t size, uint32_t mhue);

t_palette			*parse_palette(const char *format);
void				del_palette(t_palette **palette);

int8_t				interpolate(uint8_t c1, uint8_t c2, double hue);

#endif
