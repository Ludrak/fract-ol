
#pragma once

#include <stdlib.h>
#include <X11/X.h>
#include "mlx.h"
#include "color.h"
#include "utils.h"
#include "vectors.h"

#define MAX_ITERATIONS 1000
#define INF            1000

#define PALETTE_SIZE	32

typedef struct	s_screen
{
	void		*scr_ptr;
	char        *data;

	int			sl;
	int			bpp;
	int			endian;
}				t_screen;

typedef struct	s_frame
{
	void		*window;
    t_screen	*screen;
	char		*title;
	uint16_t	size_x;
	uint16_t	size_y;
    uint32_t    size_buf;
}				t_frame;

typedef struct	s_app
{
	void		*mlx;
	t_frame		*frame;
    t_vec2d     offset;
    double      zoom;
    float       zoom_factor;
    t_color     palette[PALETTE_SIZE];
}				t_app;