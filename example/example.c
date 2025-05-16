#include <libinkX.h>
#include <stdio.h>

void close_func(void) {
  printf("Close window...\n");
  printf("See you!\n");
}

int main() {
  /* Set up a new X11 GUI */
  ink_window_t window1 = i_create_window(400, 400, 200, 200);

  /* Add termination processing */
  window1.close = close_func;

  /* Without this the GUI won't appear */
  i_create_new_loop(&window1);

  /* If you want the GUI to remain visible even after the main function has
   * finished, run this before exiting. */
  i_exit_main();
}
