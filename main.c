#include <gdk/gdk.h>

static void
print_hello (GtkWidget *widget,
	     gpointer data)
{
	g_print ("Hello World 😀 dsadsa\n");
}

static GdkPixbuf*
pixbuf_slice (GdkPixbuf *src,
	       int sx, int sy,
	       int ex, int ey)
{
	int src_rowstride = gdk_pixbuf_get_rowstride (src);
	int src_width = gdk_pixbuf_get_width (src);
	int bits_per_sample = gdk_pixbuf_get_bits_per_sample (src);
	int n_channels = gdk_pixbuf_get_n_channels (src);
	int width = ex - sx;
	int height = ey - ex;
	int rowstride = (src_rowstride / src_width) * width;
	// borrowed from gdk_pixbuf_get_byte_length()
	gsize size = ((height - 1) * rowstride +
		      width * ((n_channels * bits_per_sample + 7) / 8));
	guchar *src_pixels = gdk_pixbuf_get_pixels (src);
	guint *pixels = g_try_malloc (size);

	if (!pixels)
		return NULL;

	// Copy pixels to a slice.
	// More about pixbuf structure here:
	// https://developer.gnome.org/gdk-pixbuf/2.36/gdk-pixbuf-The-GdkPixbuf-Structure.html
	for (int row = 0; row < height; row++) {
		memcpy(pixels,
		       src_pixels + (row * src_rowstride + n_channels),
		       width * n_channels);
	}

	//pixels + y * rowstride + x * n_channels;

	GdkPixbuf *pixbuf = g_object_new (GDK_TYPE_PIXBUF,
					  "colorspace", gdk_pixbuf_get_colorspace (src),
					  "n-channels", n_channels,
					  "bits-per-sample", bits_per_sample,
					  "has-alpha", gdk_pixbuf_get_has_alpha (src),
					  "width", width,
					  "height", height,
					  "rowstride", rowstride,
					  "pixels", pixels,
					  NULL);

	return pixbuf;
}

static void
activate (GtkApplication *app,
	  gpointer user_data)
{
	GtkWidget *window;
	GtkWidget *button;
	GtkWidget *button_box;
	GtkWidget *image;
	GdkPixbuf *full;
	GError *err = NULL;
	int width;

	image = gtk_image_new_from_file ("emoji_1.png");

	window = gtk_application_window_new (app);
	gtk_window_set_title (GTK_WINDOW (window), "Window");
	gtk_window_set_default_size (GTK_WINDOW (window), 200, 200);

	full = gdk_pixbuf_new_from_file ("emoji_1.png", &err);

	button_box = gtk_button_box_new (GTK_ORIENTATION_HORIZONTAL);
	gtk_container_add (GTK_CONTAINER (window), button_box);

	button = gtk_button_new_with_label ("Hello World 😀 😀😃😁🤗!");
	g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);
	gtk_container_add (GTK_CONTAINER (button_box), button);
	gtk_container_add (GTK_CONTAINER (button_box), image);

	//gtk_window_set_decorated (window, 0);
	gtk_widget_show_all (window);
}

int
main (int argc,
      char **argv)
{
	gdk_init(&argc, &argv);

	GdkWindowAttr wattr = {
			       .title = "dsads",
			       .x = 100,
			       .y = 100,
			       .width = 100,
			       .height = 200,
			       .window_type = GDK_WINDOW_TOPLEVEL
	};

	GdkWindow *win = gdk_window_new(NULL, &wattr, GDK_WA_TITLE | GDK_WA_X | GDK_WA_Y | GDK_WA_CURSOR);

	gdk_window_show(win);

	cairo_region_t *region = NULL;

	GdkDrawingContext *ctx = gdk_window_begin_draw_frame(win, region);


	while (1) {}

	return 0;

	GtkApplication *app;
	int status;


	app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
	g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
	status = g_application_run (G_APPLICATION (app), argc, argv);
	g_object_unref (app);

	return status;
}
