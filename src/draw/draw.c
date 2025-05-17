#include <X11/Xlib.h>
#include <internal.h>
#include <libinkX.h>
#include <string.h>

void i_draw(state_t state) {}

void i_text_draw(ink_text_obj obj, ink_run_window_t window) {
  GC gc;
  XFontStruct *font;

  ink_window_t win = window.window;

  font = XLoadQueryFont(win.display, obj.font);
  gc = XCreateGC(win.display, win.window, 0, 0);

  XSetFont(win.display, gc, font->fid);
  XDrawString(win.display, win.window, gc, obj.x, obj.y, obj.text,
              strlen(obj.text));
}
