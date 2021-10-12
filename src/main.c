#include <stdio.h>
#include "fractol.h"

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

t_color	smooth_color(const t_app *const app, double iterations, const double x, const double y)
{
	double log_zn;
	double nu;

	log_zn = log(x * x + y * y) / 2;
	nu = log(log_zn / LOG2) / LOG2;
	iterations = iterations + 1 - nu;
	t_color c1 = app->palette[(int)(((iterations / (double)MAX_ITERATIONS)) * PALETTE_REPEAT_AMT * app->palette_size) % app->palette_size];
	t_color c2 = app->palette[(int)((((iterations + 1) / (double)MAX_ITERATIONS)) * PALETTE_REPEAT_AMT * app->palette_size) % app->palette_size];
	return (clerp(c2, c1, iterations - floor(iterations)));
}

t_color	mandelbrot(double x0, double y0, t_app *const app)
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
		*(uint32_t *)(app->frame->screen->data + i) = mandelbrot(pos.x, pos.y, app).value & 0x00FFFFFF;
		i += 4;
		n++;
	}
	//shift_palette(app->palette, PALETTE_SIZE);
	mlx_clear_window(app->mlx, app->frame->window);
	mlx_put_image_to_window(app->frame->screen, app->frame->window, app->frame->screen->scr_ptr, 0, 0);

	if (app->mouse.action & MOUSE_LCLICK)
	{
		t_vec2d mouse_map;
		int x, y;
		mlx_mouse_get_pos(app->frame->window, &x, &y);
		mlx_mouse_move(app->frame->window, app->frame->size_x / 2, app->frame->size_y / 2);
		mlx_mouse_hide();
		mouse_map.x = mapd(x, 0, app->frame->size_x, -app->zoom, app->zoom);
		mouse_map.y = mapd(y, 0, app->frame->size_y, -app->zoom, app->zoom);
		app->offset = vec_add(app->offset, mouse_map);
		app->zoom *= 1 - app->zoom_factor;
	}
	else
		mlx_mouse_show();
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

int	on_key_pressed(int key, void *app_ptr)
{
	t_app	*app;

	if (key == 53)
		on_exit(app_ptr);
	app = (t_app *)app_ptr;
	return (0);
}

int	on_mouse_pressed(int button, int pos_x, int pos_y, void *app_ptr)
{
	t_app	*app;

	(void)pos_x;
	(void)pos_y;
	app = (t_app *)app_ptr;
	if (button == 1)
		app->mouse.action |= MOUSE_LCLICK;
	if (button == 2)
		app->mouse.action |= MOUSE_RCLICK;
	return (0);
}

int	on_mouse_released(int button, int pos_x, int pos_y, void *app_ptr)
{
	t_app	*app;

	(void)pos_x;
	(void)pos_y;
	app = (t_app *)app_ptr;
	if (button == 1)
		app->mouse.action &= ~MOUSE_LCLICK;
	if (button == 2)
		app->mouse.action &= ~MOUSE_RCLICK;
	return (0);
}

int main(int ac, char **av)
{
	t_app		app;
	t_frame		*frame;
	t_screen	*screen;

	if (ac != 2)
		return (1);

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
	app.offset = vec2d(0, 0);
	app.mouse = (t_mouse){ .action=0, .pos=vec2d(0, 0) };

/*  SETTING PALETTE */
/*	set_palette(app.palette, 0, 16, (t_color[2]){{0x000764}, {0x206acb}});
	set_palette(app.palette, 16, 42, (t_color[2]){{0x206acb}, {0xedffff}});
	set_palette(app.palette, 42, 64, (t_color[2]){{0xedffff}, {0xffaa00}});
	set_palette(app.palette, 64, 85, (t_color[2]){{0xedffff}, {0x000200}});
	set_palette(app.palette, 85, 100, (t_color[2]){{0xedffff}, {0x000764}});*/

/* 	EXPORTING PALETTE */
/*  export_palette("palette.plt", app.palette, PALETTE_SIZE); */
	t_color	*p = load_palette(av[1], &app.palette_size);
	if (!p)
		return (on_exit(&app));
	if (!(app.palette = malloc(sizeof(t_color) * app.palette_size)))
		return (0);
	for (int i = 0; i < (int)app.palette_size; i++)
		app.palette[i] = p[i];

	mlx_hook(app.frame->window, ButtonPress, ButtonPressMask, &on_mouse_pressed, &app);
	mlx_hook(app.frame->window, ButtonRelease, ButtonReleaseMask, &on_mouse_released, &app);
	mlx_hook(app.frame->window, KeyPress, KeyPressMask, &on_key_pressed, &app);
	mlx_hook(app.frame->window, DestroyNotify, NoEventMask, &on_exit, &app);
	mlx_loop_hook(app.mlx, draw_loop, &app);
	mlx_loop(app.mlx);
}
