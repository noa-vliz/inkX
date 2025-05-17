#include <X11/Xlib.h>
#include <libinkX.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

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
      break;

    case ClientMessage:
      if (iwindow.event.xclient.data.l[0] == (long)iwindow.wm_delete_window) {
        if (iwindow.close_window) {
          printf("inkX - Window close\n");
          if (iwindow.close != NULL) {
            iwindow.close();
          }

          run->running = 0;
        }
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
