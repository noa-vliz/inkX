#include <libinkX.h>

void i_close_window(ink_run_window_t *ink_window) {
  XEvent close_event;

  close_event.type = ClientMessage;
  close_event.xclient.window = ink_window->window.window;
  close_event.xclient.message_type = ink_window->window.wm_delete_window;
  close_event.xclient.format = 32;
  close_event.xclient.data.l[0] = ink_window->window.wm_delete_window;
  close_event.xclient.data.l[1] = CurrentTime;

  XSendEvent(ink_window->window.display, ink_window->window.window, False,
             NoEventMask, &close_event);
  XFlush(ink_window->window.display);
}
