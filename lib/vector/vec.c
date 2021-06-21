/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 16:20:33 by lrobino           #+#    #+#             */
/*   Updated: 2020/07/14 16:21:00 by lrobino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vectors.h"

t_vec2d		vec2d(double x, double y)
{
	return (create_vector(x, y));
}

t_vec2f		vec2f(float x, float y)
{
	return (create_vectorf(x, y));
}

t_vec2i		vec2i(int x, int y)
{
	return (create_vectori(x, y));
}

/*
**  UTIL
*/

t_vec2d		vec_set_mag(t_vec2d vec, float mag)
{
	t_vec2d v;

	v = vec_norm(vec);
	v = vec_multf(vec, mag);
	return (v);
}
