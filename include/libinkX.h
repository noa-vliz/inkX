#ifndef __LIB_INK_X
#define __LIB_INK_X
#include <X11/Xlib.h>

typedef struct {
  Display *display;
  Window window;
  XEvent event;
  int screen;
  Atom wm_delete_window;
  int close_window;
  void (*close)(void);
} ink_window_t;

typedef struct {
  int running;
  ink_window_t window;
} ink_run_window_t;

/*
typedef struct {
} ink_draw_objects_t;
*/

/* Create a new ink_window_t instance */
ink_window_t i_create_window(int x, int y, int width, int height,
                             const char *title);

/* Create a new thread to draw the GUI */
ink_run_window_t *i_create_new_loop(ink_window_t *ink_window);

/* close a window */
void i_close_window(ink_run_window_t *ink_window);

/* Optionally, keep the GUI after main exits */
void i_exit_main();

#endif /* __LIB_INK_X */
