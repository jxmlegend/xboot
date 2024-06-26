/*
 * wboxtest/graphic/polygon.c
 */

#include <wboxtest.h>

struct wbt_polygon_pdata_t
{
	struct window_t * w;
};

static void * polygon_setup(struct wboxtest_t * wbt)
{
	struct wbt_polygon_pdata_t * pdat;

	pdat = malloc(sizeof(struct wbt_polygon_pdata_t));
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

static void polygon_clean(struct wboxtest_t * wbt, void * data)
{
	struct wbt_polygon_pdata_t * pdat = (struct wbt_polygon_pdata_t *)data;

	if(pdat)
	{
		window_free(pdat->w);
		free(pdat);
	}
}

static void draw_polygon(struct window_t * w, void * o)
{
	struct wbt_polygon_pdata_t * pdat = (struct wbt_polygon_pdata_t *)o;
	struct surface_t * s = pdat->w->s;
	struct color_t c;
	int x[10], y[10];
	int thickness;

	int n = wboxtest_random_int(2, 10);
	for(int i = 0; i < n; i++)
	{
		x[i] = wboxtest_random_int(0, surface_get_width(s));
		y[i] = wboxtest_random_int(0, surface_get_height(s));
	}
	color_init(&c, rand() & 0xff, rand() & 0xff, rand() & 0xff, 255);
	thickness = wboxtest_random_int(0, 50);

	surface_shape_save(s);
	surface_shape_move_to(s, x[0], y[0]);
	for(int i = 1; i < n; i++)
		surface_shape_line_to(s, x[i], y[i]);
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

static void polygon_run(struct wboxtest_t * wbt, void * data)
{
	struct wbt_polygon_pdata_t * pdat = (struct wbt_polygon_pdata_t *)data;
	int frame = 600;

	if(pdat)
	{
		while(frame-- > 0)
		{
			ktime_t timeout = ktime_add_ms(ktime_get(), 16);
			window_present(pdat->w, pdat, draw_polygon);
			while(ktime_before(ktime_get(), timeout));
		}
	}
}

static struct wboxtest_t wbt_polygon = {
	.group	= "graphic",
	.name	= "polygon",
	.setup	= polygon_setup,
	.clean	= polygon_clean,
	.run	= polygon_run,
};

static __init void polygon_wbt_init(void)
{
	register_wboxtest(&wbt_polygon);
}

static __exit void polygon_wbt_exit(void)
{
	unregister_wboxtest(&wbt_polygon);
}

wboxtest_initcall(polygon_wbt_init);
wboxtest_exitcall(polygon_wbt_exit);
