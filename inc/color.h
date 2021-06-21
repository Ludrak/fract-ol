#ifndef COLOR_H
# define COLOR_H

#include <stdlib.h>


typedef struct s_color_channel
{
	uint8_t	g;
	uint8_t	b;
	uint8_t	r;
	uint8_t	a;
}	t_color_channel;

typedef union	u_color
{
	uint32_t		value;
	t_color_channel	channels;
}				t_color;

t_color         color(uint8_t r, uint8_t g, uint8_t b);
t_color         brightness(uint8_t i);

t_color         clerp(t_color from, t_color to, float lerp);

void    		set_palette(t_color *palette, size_t index, size_t size, t_color colors[2]);

#endif