/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_point.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 15:11:53 by yguaye            #+#    #+#             */
/*   Updated: 2018/01/20 16:55:34 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft_base/stringft.h>
#include <libft_base/character.h>
#include "fractol.h"

static t_bool	get_hex_pair(char c1, char c2, uint8_t *res)
{
	if (!((c1 >= '0' && c1 <= '9') || (c1 >= 'A' && c1 <= 'F')) ||
			!((c2 >= '0' && c2 <= '9') || (c2 >= 'A' && c2 <= 'F')))
		return (0);
	*res = (c1 >= '0' && c1 <= '9' ? c1 - '0' : c1 - 'A' + 10) * 16;
	*res += (c2 >= '0' && c2 <= '9' ? c2 - '0' : c2 - 'A' + 10);
	return (TRUE);
}

static t_bool	get_color_code(const char *format, int i, t_color_point *p)
{
	if (ft_strlen(format) < 7 || format[i] != '#' ||
			!get_hex_pair(format[i + 1], format[i + 2], &p->r) ||
			!get_hex_pair(format[i + 3], format[i + 4], &p->g) ||
			!get_hex_pair(format[i + 5], format[i + 6], &p->b) ||
			(format[i + 7] != '@' && format[i + 7] != ',' && format[i + 7]))
		return (FALSE);
	return (TRUE);
}

static t_bool	get_color_pos(const char *format, int *i, t_color_point *p)
{
	++*i;
	p->pos = (uint32_t)ft_atoi(format + *i);
	if (!ft_isdigit(format[*i]))
		return (FALSE);
	while (ft_isdigit(format[*i]))
		++*i;
	if (format[*i] && format[*i] != ',')
		return (FALSE);
	return (TRUE);
}

static t_bool	get_color_type(const char *format, int *i, t_color_point *p)
{
	t_bool			neg;

	neg = FALSE;
	if (format[*i + 1] == '-')
	{
		neg = TRUE;
		++*i;
	}
	if (!ft_isdigit(format[*i + 1]) || format[*i + 2])
		return (FALSE);
	p->type = (format[*i + 1] - '0') * (neg ? -1 : 1);
	return (TRUE);
}

t_list			*get_color_point(const char *format)
{
	t_color_point	p;
	int				i;

	i = 0;
	ignore_ws(&i, format);
	if (!get_color_code(format, i, &p))
		return (NULL);
	i += 7;
	if (format[i] == '@')
	{
		if (!get_color_pos(format, &i, &p))
			return (NULL);
	}
	else
		p.pos = 0;
	if (format[i] == ',')
	{
		if (!get_color_type(format, &i, &p))
			return (NULL);
	}
	else
		p.type = LINEAR;
	return (ft_lstnew(&p, sizeof(t_color_point)));
}
