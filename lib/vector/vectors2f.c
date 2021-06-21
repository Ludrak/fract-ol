/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors2f.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 13:59:40 by lrobino           #+#    #+#             */
/*   Updated: 2020/07/14 16:28:47 by lrobino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vectors.h"
#include <math.h>

/*
**  RETURN THE ADDITION OF VA & VB
*/

t_vec2f		vecf_add(t_vec2f va, t_vec2f vb)
{
	t_vec2f	vec;

	vec.x = va.x + vb.x;
	vec.y = va.y + vb.y;
	return (vec);
}

/*
**  RETURN THE SUBSTRACTION OF VA & VB
*/

t_vec2f		vecf_sub(t_vec2f va, t_vec2f vb)
{
	t_vec2f vec;

	vec.x = va.x - vb.x;
	vec.y = va.y - vb.y;
	return (vec);
}

/*
**  RETURN THE PRODUCT OF VA & VB
*/

t_vec2f		vecf_mult(t_vec2f va, t_vec2f vb)
{
	t_vec2f vec;

	vec.x = va.x * vb.x;
	vec.y = va.y * vb.y;
	return (vec);
}

/*
**  RETURN THE NORMALIZED V
*/

t_vec2f		vecf_norm(t_vec2f v)
{
	t_vec2f	vec;
	float	mag;

	mag = vecf_mag(v);
	vec.x = v.x / mag;
	vec.y = v.y / mag;
	return (vec);
}

/*
**  RETURN THE MAGNITUDE OF V
*/

float		vecf_mag(t_vec2f v)
{
	return ((float)sqrtf((v.x * v.x) + (v.y * v.y)));
}
