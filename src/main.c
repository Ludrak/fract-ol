#include <stdio.h>
#include "fractol.h"

t_color	smooth_color(const t_app *const app, double iterations, const double x, const double y)
{
	double log_zn;
	double nu;

	log_zn = log(x * x + y * y) / 2;
	nu = log(log_zn / LOG2) / LOG2;
	iterations = iterations + 1 - nu;
	t_color c1 = app->palette[(int)floor(iterations) % PALETTE_SIZE];
	t_color c2 = app->palette[((int)floor(iterations) + 1) % PALETTE_SIZE];
	return (clerp(c2, c1, iterations - floor(iterations)));
}

t_color	mandelbrot(double x0, double y0, const t_app *const app)
{
	double	x;
	double	y;
	double	x_squared;
	double	y_squared;
	double	iterations;

	iterations = 0;
	x = x0;
	y = y0;
	while (fabs(x + y) < INF && iterations < MAX_ITERATIONS)
	{
		x_squared = x * x - y * y;
		y_squared = 2 * x * y;
		x = x_squared + x0;
		y = y_squared + y0;
		iterations++;
	}
	if (iterations < MAX_ITERATIONS)
		return (smooth_color(app, iterations, x, y));
	else
		return (brightness(0));
}

void	map_complex_space
	(const t_app *const app, const uint32_t i, t_vec2d *pos, t_vec2d off, const double zoom_factor)
{
	double	sc_x;
	double	sc_y;
	double	max_sz;
	double  diff;

	sc_x = i % app->frame->size_x;
	sc_y = i / app->frame->size_x;
	max_sz = app->frame->size_x > app->frame->size_y ? app->frame->size_x : app->frame->size_y;
	pos->x = mapd(sc_x, 0, max_sz, -zoom_factor + off.x, zoom_factor + off.x);
	diff = (max_sz - app->frame->size_y) * 0.5f;
	pos->y = mapd(sc_y, -diff, max_sz - diff, -zoom_factor + off.y, zoom_factor + off.y);
}

void shift_palette(t_color *palette, size_t size)
{
	size_t	i;
	t_color buf;

	if (!palette)
		return;
	buf = *palette;
	i = 0;
	while (i < size - 1)
	{
		palette[i] = palette[i + 1];
		i++;
	}
	palette[i] = buf;
}

int draw_loop(void *app_ptr)
{
	t_app			*app;
	uint32_t		i;
	uint32_t		n;
	t_vec2d			pos;

	app = (t_app *)app_ptr;
	i = 0;
	n = 0;
	while (i < app->frame->size_buf - 1)
	{
		map_complex_space(app, n, &pos, app->offset, app->zoom);
		*(uint32_t *)(app->frame->screen->data + i) = mandelbrot(pos.x, pos.y, app).value;
		i += 4;
		n++;
	}
	shift_palette(app->palette, PALETTE_SIZE);
	app->zoom *= 1 - app->zoom_factor;
	mlx_put_image_to_window(app->frame->screen, app->frame->window, app->frame->screen->scr_ptr, 0, 0);
	mlx_do_sync(app->mlx);
	return (0);
}

int	on_exit(void *app_ptr)
{
	t_app	*app;

	app = (t_app *)app_ptr;
	exit(0);
	return (0);
}

int main()
{
	t_app		app;
	t_frame		*frame;
	t_screen	*screen;

	app.mlx = mlx_init();
	frame = malloc(sizeof(t_frame));
	frame->size_x = 1280;
	frame->size_y = 720;
	frame->size_buf = frame->size_x * frame->size_y * 4;
	frame->title = "fract-ol";
	frame->window = mlx_new_window(app.mlx, frame->size_x, frame->size_y, frame->title);
	screen = malloc(sizeof(t_screen));
	screen->scr_ptr = mlx_new_image(app.mlx, frame->size_x, frame->size_y);
	screen->data = (char *)mlx_get_data_addr(screen->scr_ptr, &screen->bpp, &screen->sl, &screen->endian);
	frame->screen = screen;
	app.frame = frame;
	app.zoom_factor = 0.05;
	app.zoom = 4;
	app.offset = vec2d(ZOOM_RE, -ZOOM_IM);

	/** PALETTE 256 **/
	#if PALETTE_SIZE == 256
	set_palette(app.palette, 0, 32, (t_color[2]){{0xffffff}, {0xf7da57}});
	set_palette(app.palette, 33, 44, (t_color[2]){{0xf7da57}, {0xe8761e}});
	set_palette(app.palette, 44, 55, (t_color[2]){{0xe8761e}, {0x0}});
	set_palette(app.palette, 55, 65, (t_color[2]){{0xffffff}, {0x0c52f5}});
	set_palette(app.palette, 65, 86, (t_color[2]){{0xffffff}, {0xf7da57}});
	set_palette(app.palette, 87, 92, (t_color[2]){{0xf7da57}, {0xe8761e}});
	set_palette(app.palette, 92, 98, (t_color[2]){{0xe8761e}, {0x0}});
	set_palette(app.palette, 98, 112, (t_color[2]){{0xffffff}, {0x0c52f5}});
	set_palette(app.palette, 112, 135, (t_color[2]){{0xffffff}, {0xf7da57}});
	set_palette(app.palette, 135, 145, (t_color[2]){{0xf7da57}, {0xe8761e}});
	set_palette(app.palette, 145, 150, (t_color[2]){{0xe8761e}, {0x0}});
	set_palette(app.palette, 150, 160, (t_color[2]){{0xffffff}, {0x0c52f5}});
	set_palette(app.palette, 160, 165, (t_color[2]){{0xffffff}, {0xf7da57}});
	set_palette(app.palette, 165, 180, (t_color[2]){{0xf7da57}, {0xe8761e}});
	set_palette(app.palette, 180, 185, (t_color[2]){{0xe8761e}, {0x0}});
	set_palette(app.palette, 185, 255, (t_color[2]){{0xffffff}, {0x0c52f5}});
	#endif
	/**			**/

	/** PALETTE 32 **/
	#if PALETTE_SIZE == 32
	set_palette(app.palette, 0, 10, (t_color[2]){{0xffffff}, {0xf7da57}});
	set_palette(app.palette, 10, 16, (t_color[2]){{0xf7da57}, {0xe8761e}});
	set_palette(app.palette, 16, 18, (t_color[2]){{0xe8761e}, {0x0}});
	set_palette(app.palette, 18, 31, (t_color[2]){{0xffffff}, {0x0c52f5}});
	#endif
	/**			   **/


	/** PALETTE 16 **/
	#if PALETTE_SIZE == 16
	set_palette(app.palette, 0, 5, (t_color[2]){{0xffffff}, {0xf7da57}});
	set_palette(app.palette, 5, 8, (t_color[2]){{0xf7da57}, {0xe8761e}});
	set_palette(app.palette, 8, 9, (t_color[2]){{0xe8761e}, {0x0}});
	set_palette(app.palette, 9, 16, (t_color[2]){{0xffffff}, {0x0c52f5}});
	#endif
	/**			   **/

	mlx_hook(app.frame->window, DestroyNotify, NoEventMask, &on_exit, &app);
	mlx_loop_hook(app.mlx, draw_loop, &app);
	mlx_loop(app.mlx);
}
