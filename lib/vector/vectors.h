/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 16:32:27 by lrobino           #+#    #+#             */
/*   Updated: 2020/07/14 16:36:42 by lrobino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORS_H
# define VECTORS_H

# ifndef PI
#  define PI	3.1415926535f
# endif
# define TWO_PI	6.2831853071f

typedef struct	s_vec2d
{
	double	x;
	double	y;
}				t_vec2d;

typedef struct	s_vec2f
{
	float	x;
	float	y;
}				t_vec2f;

typedef struct	s_vec2i
{
	int		x;
	int		y;
}				t_vec2i;

/*
**  VECTOR UTILS 2 DOUBLE
*/
t_vec2d			vec2d(double x, double y);
t_vec2d			create_vector(double x, double y);
t_vec2d			vec_add(t_vec2d va, t_vec2d vb);
t_vec2d			vec_sub(t_vec2d va, t_vec2d vb);
t_vec2d			vec_mult(t_vec2d va, t_vec2d vb);
t_vec2d			vec_multf(t_vec2d v, double amt);
t_vec2d			vec_norm(t_vec2d vec);
double			vec_mag(t_vec2d vec);
double			vec_dot (t_vec2d va, t_vec2d vb);
t_vec2d			vec_set_mag(t_vec2d vec, float mag);

/*
**  VECTOR UTILS 2 FLOAT
*/
t_vec2f			vec2f(float x, float y);
t_vec2f			create_vectorf(float x, float y);
t_vec2f			vecf_add(t_vec2f va, t_vec2f vb);
t_vec2f			vecf_sub(t_vec2f va, t_vec2f vb);
t_vec2f			vecf_mult(t_vec2f va, t_vec2f vb);
t_vec2f			vecf_norm(t_vec2f vec);
float			vecf_mag(t_vec2f vec);
float			vecf_dot (t_vec2f va, t_vec2f vb);

/*
**  VECTOR UTILS 2 INT
*/

t_vec2i			vec2i(int x, int y);
t_vec2i			create_vectori(int x, int y);
t_vec2i			veci_add(t_vec2i va, t_vec2i vb);
t_vec2i			veci_sub(t_vec2i va, t_vec2i vb);
t_vec2i			veci_mult(t_vec2i va, t_vec2i vb);
t_vec2i			veci_norm(t_vec2i vec);
int				veci_mag(t_vec2i vec);

#endif
