#include <libinkX.h>
#include <stdio.h>

void close_window_c(void) { printf("exit!\n"); }

int main() {
  ink_window_t window1 = i_create_window(100, 100, 300, 300);
  window1.close = close_window_c;

  ink_run_window_t *run = i_create_new_loop(&window1);

  i_exit_main();
}
