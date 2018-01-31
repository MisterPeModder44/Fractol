/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandel_julia.cl                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 11:05:51 by yguaye            #+#    #+#             */
/*   Updated: 2018/01/31 15:53:50 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

kernel void			mandel_julia(global float2 *c, global int *i)
{
	private size_t	pos;
	private double	tmp;
	private float2	point;

	pos = get_global_id(0);
	i[pos] = 0;
	point.x = .0;
	point.y = .0;
	while (point.x * point.x + point.y * point.y < 4 && i[pos] < 1000)
	{
		tmp = point.x * point.x - point.y * point.y + c->x;
		point.y = 2 * point.x * point.y + c->y;
		point.x = tmp;
		++i[pos];
	}
}
