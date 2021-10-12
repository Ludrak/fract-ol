
#ifndef INPUT_H
# define INPUT_H

#include <stdlib.h>
#include "vectors.h"

#define MOUSE_LCLICK 		1
#define MOUSE_RCLICK 		2
#define MOUSE_SCROLL_IN		4
#define MOUSE_SCROLL_OUT	8

typedef struct	s_mouse
{
	t_vec2d	pos;
	uint8_t	action;
}				t_mouse;

#endif