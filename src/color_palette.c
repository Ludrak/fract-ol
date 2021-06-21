
#include "color.h"

void    set_palette(t_color *palette, size_t index, size_t end, t_color colors[2])
{
    size_t i = 0;

    i = index;
    while (i < end)
    {
        palette[i] = clerp(colors[0], colors[1], (float)(end - i) / (float)(end - index));
        i++;
    }
}