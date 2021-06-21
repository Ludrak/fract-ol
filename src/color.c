
#include "color.h"

t_color         color(uint8_t r, uint8_t g, uint8_t b)
{
    t_color col;

    col.channels.r = r;
    col.channels.g = g;
    col.channels.b = b;
    col.channels.a = 0x0;
    return (col);
}

t_color         brightness(uint8_t i)
{
    t_color col;

    col.channels.r = i;
    col.channels.g = i;
    col.channels.b = i;
    col.channels.a = 0x0;
    return (col);
}

t_color         clerp(t_color from, t_color to, float lerp)
{
    t_color lerped;

    lerped.channels.r = from.channels.r * lerp + to.channels.r * (1.0F - lerp);
    lerped.channels.g = from.channels.g * lerp + to.channels.g * (1.0F - lerp);
    lerped.channels.b = from.channels.b * lerp + to.channels.b * (1.0F - lerp);
    return (lerped);
}
