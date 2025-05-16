#ifndef __LIB_INK_X
#define __LIB_INK_X
#include <X11/Xlib.h>

typedef struct {
  Display *display;
  Window window;
  XEvent event;
  int screen;
  Atom wm_delete_window;
  void (*close)(void);
} ink_window_t;

typedef struct {
  int running;
  ink_window_t window;
} ink_run_window_t;

ink_window_t i_create_window(int x, int y, int width, int height);
ink_run_window_t *i_create_new_loop(ink_window_t *ink_window);
void i_close_window(ink_run_window_t ink_window);
void i_exit_main();

#endif /* __LIB_INK_X */
