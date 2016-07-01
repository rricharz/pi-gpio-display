
#include <cairo.h>

void application_init();
void application_draw(cairo_t *cr, int width, int height);
int application_on_timer_event();
int application_clicked(int button, int x, int y);
void application_quit();
