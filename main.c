/*
 * 
 * main.c
 * provides a simple framework for basic drawing with cairo and gtk+ 3.0
 * define main window in application.h
 * and your cairo drawing in application.c
 * 
 * The framework provides functions to
 *   a function to draw using cairo
 *     some nice examples of cairo snippets can be found at
 *     http://http://cairographics.org/samples/
 *   a function to initialize your code
 *   a function to exit your code
 *   a peridicaly called function
 *   a function called if the mouse is clicked 
 * 
 * Copyright 2016  rricharz
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */

#include <stdio.h>
#include <string.h>
#include <cairo.h>
#include <gtk/gtk.h>

#include "main.h"
#include "application.h"

static void do_drawing(cairo_t *, GtkWidget *);

static gboolean on_draw_event(GtkWidget *widget, cairo_t *cr, 
    gpointer user_data)
{  
	do_drawing(cr, widget);  
	return FALSE;
}

static gboolean on_timer_event(GtkWidget *widget)
{
	if (application_on_timer_event())
	  gtk_widget_queue_draw(widget);
	return TRUE;
}

static gboolean clicked(GtkWidget *widget, GdkEventButton *event, gpointer user_data)
{
    if (application_clicked(event->button, event->x, event->y))
        gtk_widget_queue_draw(widget);
    return TRUE;
}

static void on_quit_event()
{
	application_quit();
	gtk_main_quit();
}

static void do_drawing(cairo_t *cr, GtkWidget *widget)
{
	int width, height;
	GtkWidget *win = gtk_widget_get_toplevel(widget);
	gtk_window_get_size(GTK_WINDOW(win), &width, &height);
	application_draw(cr, width, height);     
}

int main (int argc, char *argv[])
{
	GtkWidget *darea;
	GtkWidget *window;
  
	gtk_init(&argc, &argv);

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

	darea = gtk_drawing_area_new();
	gtk_container_add(GTK_CONTAINER(window), darea);
	gtk_widget_add_events(window, GDK_BUTTON_PRESS_MASK);

	g_signal_connect(G_OBJECT(darea), "draw",  G_CALLBACK(on_draw_event), NULL);
	g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(on_quit_event), NULL);
	g_signal_connect(G_OBJECT(window), "button-press-event", G_CALLBACK(clicked), NULL);
  
    if (TIME_INTERVAL > 0) {
		// Add timer event
		// Register the timer and set time in mS.
		// The timer_event() function is called repeatedly until it returns FALSE. 
		g_timeout_add(TIME_INTERVAL, (GSourceFunc) on_timer_event, (gpointer) window);
	}

	gtk_window_set_default_size(GTK_WINDOW(window), WINDOW_WIDTH, WINDOW_HEIGHT); 
	gtk_window_set_title(GTK_WINDOW(window), WINDOW_NAME);
	
	if (strlen(ICON_NAME) > 0) {
		gtk_window_set_icon_from_file(GTK_WINDOW(window), ICON_NAME, NULL);	
	}
	
	application_init();

	gtk_widget_show_all(window);

	gtk_main();

	return 0;
}
