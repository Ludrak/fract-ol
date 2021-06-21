/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 16:23:10 by lrobino           #+#    #+#             */
/*   Updated: 2020/07/14 16:23:19 by lrobino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vectors.h"

/*
**  CREATES A SIMPLE 2d VECTOR FROM X and Y
*/

t_vec2d		create_vector(double x, double y)
{
	t_vec2d vec;

	vec.x = x;
	vec.y = y;
	return (vec);
}

/*
**  CREATES A SIMPLE 2d VECTOR FROM X and Y
*/

t_vec2f		create_vectorf(float x, float y)
{
	t_vec2f vec;

	vec.x = x;
	vec.y = y;
	return (vec);
}

/*
**  CREATES A SIMPLE 2d VECTOR FROM X and Y
*/

t_vec2i		create_vectori(int x, int y)
{
	t_vec2i vec;

	vec.x = x;
	vec.y = y;
	return (vec);
}

/*
**  MULTIPLY A VECTOR BY SOME CONSTANT FLOAT AMOUNT
*/

t_vec2d		vec_multf(t_vec2d v, double amt)
{
	t_vec2d vec;

	vec.x = v.x * amt;
	vec.y = v.y * amt;
	return (vec);
}

/*
**  RETURNS THE DOT PRODUCT OF VA & VB
*/

double		vec_dot(t_vec2d va, t_vec2d vb)
{
	return (va.x * vb.x + va.y * vb.y);
}
