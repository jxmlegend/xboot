/*
 * wboxtest/graphic/triangle.c
 */

#include <wboxtest.h>

struct wbt_triangle_pdata_t
{
	struct window_t * w;
};

static void * triangle_setup(struct wboxtest_t * wbt)
{
	struct wbt_triangle_pdata_t * pdat;

	pdat = malloc(sizeof(struct wbt_triangle_pdata_t));
	if(!pdat)
		return NULL;

	pdat->w = window_alloc(NULL, NULL);
	if(!pdat->w)
	{
		free(pdat);
		return NULL;
	}
	return pdat;
}

static void triangle_clean(struct wboxtest_t * wbt, void * data)
{
	struct wbt_triangle_pdata_t * pdat = (struct wbt_triangle_pdata_t *)data;

	if(pdat)
	{
		window_free(pdat->w);
		free(pdat);
	}
}

static void draw_triangle(struct window_t * w, void * o)
{
	struct wbt_triangle_pdata_t * pdat = (struct wbt_triangle_pdata_t *)o;
	struct surface_t * s = pdat->w->s;
	struct color_t c;
	int thickness;

	int x0 = wboxtest_random_int(0, surface_get_width(s));
	int y0 = wboxtest_random_int(0, surface_get_height(s));
	int x1 = wboxtest_random_int(0, surface_get_width(s));
	int y1 = wboxtest_random_int(0, surface_get_height(s));
	int x2 = wboxtest_random_int(0, surface_get_width(s));
	int y2 = wboxtest_random_int(0, surface_get_height(s));
	color_init(&c, rand() & 0xff, rand() & 0xff, rand() & 0xff, 255);
	thickness = wboxtest_random_int(0, 50);

	surface_shape_save(s);
	surface_shape_move_to(s, x0, y0);
	surface_shape_line_to(s, x1, y1);
	surface_shape_line_to(s, x2, y2);
	surface_shape_close_path(s);
	surface_shape_set_source_color(s, &c);
	if(thickness > 0)
	{
		surface_shape_set_line_width(s, thickness);
		surface_shape_stroke(s);
	}
	else
	{
		surface_shape_fill(s);
	}
	surface_shape_restore(s);
}

static void triangle_run(struct wboxtest_t * wbt, void * data)
{
	struct wbt_triangle_pdata_t * pdat = (struct wbt_triangle_pdata_t *)data;
	int frame = 600;

	if(pdat)
	{
		while(frame-- > 0)
		{
			ktime_t timeout = ktime_add_ms(ktime_get(), 16);
			window_present(pdat->w, pdat, draw_triangle);
			while(ktime_before(ktime_get(), timeout));
		}
	}
}

static struct wboxtest_t wbt_triangle = {
	.group	= "graphic",
	.name	= "triangle",
	.setup	= triangle_setup,
	.clean	= triangle_clean,
	.run	= triangle_run,
};

static __init void triangle_wbt_init(void)
{
	register_wboxtest(&wbt_triangle);
}

static __exit void triangle_wbt_exit(void)
{
	unregister_wboxtest(&wbt_triangle);
}

wboxtest_initcall(triangle_wbt_init);
wboxtest_exitcall(triangle_wbt_exit);
