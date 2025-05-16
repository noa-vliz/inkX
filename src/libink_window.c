#include <X11/X.h>
#include <X11/Xlib.h>
#include <bits/pthreadtypes.h>
#include <libinkX.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

ink_window_t i_create_window(int x, int y, int width, int height) {
  ink_window_t window;

  window.close = NULL;
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

  return window;
}

void draw() {}

void *window_main_loop(void *arg) {
  ink_run_window_t *run = (ink_run_window_t *)arg;
  ink_window_t iwindow = run->window;

  run->running = 1;

  while (run->running) {
    XNextEvent(iwindow.display, &iwindow.event);

    switch (iwindow.event.type) {
    case Expose:
      draw();
      break;

    case KeyPress:
      printf("inkX: key pressed\n");
      break;

    case ClientMessage:
      if (iwindow.event.xclient.data.l[0] == (long)iwindow.wm_delete_window) {
        printf("inkX: Window close\n");
        if (iwindow.close != NULL) {
          iwindow.close();
        }

        run->running = 0;
        break;
      }
      break;
    }
  }

  free(run);
  return NULL;
}

ink_run_window_t *i_create_new_loop(ink_window_t *ink_window) {
  ink_run_window_t *data = malloc(sizeof(ink_run_window_t));
  if (!data)
    return NULL;

  data->window = *ink_window;
  data->running = 1;

  pthread_t thread;
  pthread_create(&thread, NULL, window_main_loop, data);
  pthread_detach(thread);

  return data;
}

void i_exit_main() { pthread_exit(NULL); }
