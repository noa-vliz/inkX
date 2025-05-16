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
      i_create_window(400, 400, 200, 200, "Simple libinkX example");

  /* Set the close event handler */
  window1.close = close_func;

  /* Start the event loop (required for GUI to appear) */
  i_create_new_loop(&window1);

  /* Optionally, keep the GUI after main exits */
  i_exit_main();
}
