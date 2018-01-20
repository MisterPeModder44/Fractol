/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   palette_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 16:51:10 by yguaye            #+#    #+#             */
/*   Updated: 2018/01/20 17:10:45 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft_base/stringft.h>
#include <libft_base/character.h>
#include "palette.h"

void				ignore_ws(int *i, const char *str)
{
	while (str[*i] && ft_isspace(str[*i]))
		++*i;
}

static t_bool		next_num(int *i, const char *str, uint32_t *num)
{
	if (str[*i] == '-')
		return (FALSE);
	*num = (uint32_t)ft_atoi(str + *i);
	while (str[*i] && (ft_isspace(str[*i]) || ft_isdigit(str[*i])))
		++*i;
	return (TRUE);
}

t_bool				get_size(char **tab, size_t len, uint32_t *nums)
{
	const char		*str;
	int				i;

	str = tab[len - 1];
	i = 0;
	ignore_ws(&i, str);
	++i;
	if (str[i - 1] != '[' || !next_num(&i, str, nums))
		return (FALSE);
	nums[1] = 100;
	if (str[i] == ',')
	{
		++i;
		if (!next_num(&i, str, nums + 1))
			return (FALSE);
	}
	if (str[i] != ']' || (str[i] && str[i + 1]))
		return (FALSE);
	return (TRUE);
}
