/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clamp.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 18:18:45 by yguaye            #+#    #+#             */
/*   Updated: 2018/02/08 18:20:15 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

double				clamp(double num, double min, double max)
{
	double			tmp;

	tmp = num < min ? min : num;
	return (tmp > max ? max : num);
}
