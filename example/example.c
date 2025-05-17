#include <libinkX.h>
#include <stdio.h>
#include <unistd.h>

void close_func(void) {
  printf("Close window...\n");
  printf("See you!\n");
}

int main() {
  /* Create a window at (400, 400) with size 200x200 */
  ink_window_t window1 =
      i_create_window(400, 400, 200, 200, "Simple inkX example");

  ink_window_t window2 =
      i_create_window(400, 400, 200, 200, "Simple inkX example(2)");

  /* Set the close event handler */
  window1.close = close_func;
  window2.close = NULL;

  /* Start the event loop (required for GUI to appear) */
  i_create_new_loop(&window1);
  i_create_new_loop(&window2);

  /* Optionally, keep the GUI after main exits */
  i_exit_main();
}
