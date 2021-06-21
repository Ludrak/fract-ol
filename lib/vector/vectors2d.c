/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors2d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 16:24:32 by lrobino           #+#    #+#             */
/*   Updated: 2020/07/14 16:25:31 by lrobino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vectors.h"
#include <math.h>

/*
**  RETURN THE ADDITION OF VA & VB
*/

t_vec2d		vec_add(t_vec2d va, t_vec2d vb)
{
	t_vec2d	vec;

	vec.x = va.x + vb.x;
	vec.y = va.y + vb.y;
	return (vec);
}

/*
**  RETURN THE SUBSTRACTION OF VA & VB
*/

t_vec2d		vec_sub(t_vec2d va, t_vec2d vb)
{
	t_vec2d	vec;

	vec.x = va.x - vb.x;
	vec.y = va.y - vb.y;
	return (vec);
}

/*
**  RETURN THE PRODUCT OF VA & VB
*/

t_vec2d		vec_mult(t_vec2d va, t_vec2d vb)
{
	t_vec2d	vec;

	vec.x = va.x * vb.x;
	vec.y = va.y * vb.y;
	return (vec);
}

/*
**  RETURN THE NORMALIZED V
*/

t_vec2d		vec_norm(t_vec2d v)
{
	t_vec2d	vec;
	double	mag;

	mag = vec_mag(v);
	vec.x = v.x / mag;
	vec.y = v.y / mag;
	return (vec);
}

/*
**  RETURN THE MAGNITUDE OF V
*/

double		vec_mag(t_vec2d v)
{
	return (sqrt((v.x * v.x) + (v.y * v.y)));
}
