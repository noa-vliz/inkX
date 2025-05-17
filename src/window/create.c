#include <libinkX.h>
#include <stdio.h>
#include <stdlib.h>

ink_window_t i_create_window(int x, int y, int width, int height,
                             const char *title) {
  ink_window_t window;

  window.close = NULL;
  window.close_window = 1;

  window.display = XOpenDisplay(NULL);
  if (window.display == NULL) {
    fprintf(stderr, "inkX: Unable to connect Xserver\n");
    exit(1);
  }

  window.screen = DefaultScreen(window.display);

  window.window = XCreateSimpleWindow(
      window.display, RootWindow(window.display, window.screen), x, y, width,
      height, 1, BlackPixel(window.display, window.screen),
      WhitePixel(window.display, window.screen));

  window.wm_delete_window =
      XInternAtom(window.display, "WM_DELETE_WINDOW", False);

  XSetWMProtocols(window.display, window.window, &window.wm_delete_window, 1);
  XSelectInput(window.display, window.window,
               ExposureMask | KeyPressMask | StructureNotifyMask);
  XMapWindow(window.display, window.window);

  XStoreName(window.display, window.window, title);

  return window;
}
