#ifndef __LIB_INK_X
#define __LIB_INK_X
#include <X11/Xlib.h>

#ifdef __cplusplus
extern "C" {
#endif

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

typedef struct {
  int x;
  int y;
  char *text;
  void (*onclick)(void);
  void (*onfocus)(void);
} ink_text_obj;

/* Create a new ink_window_t instance */
ink_window_t i_create_window(int x, int y, int width, int height,
                             const char *title);

/*  */
ink_window_t i_set_close_event(ink_window_t window);

ink_window_t i_set_close_event(ink_window_t window);

ink_window_t i_set_close_event(ink_window_t window);

/* Create a new thread to draw the GUI */
ink_run_window_t *i_create_new_loop(ink_window_t *ink_window);

/* close a window */
void i_close_window(ink_run_window_t *ink_window);

/* Optionally, keep the GUI after main exits */
void i_exit_main();

#ifdef __cplusplus
}
#endif

#endif /* __LIB_INK_X */
