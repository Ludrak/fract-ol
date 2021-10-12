
#include "vectors.h"

t_vec2d vec_lerp(t_vec2d from, t_vec2d to, float lerp)
{
    t_vec2d lerped;

    lerped.x = from.x * lerp + to.x * (1.0F - lerp);
    lerped.y = from.y * lerp + to.y * (1.0F - lerp);
    return (lerped);
}