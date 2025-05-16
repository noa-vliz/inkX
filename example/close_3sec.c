#include <libinkX.h>
#include <unistd.h>

int main() {
  ink_window_t window = i_create_window(200, 300, 200, 300, "Close 3sec");

  window.close_window = 0;

  ink_run_window_t *run = i_create_new_loop(&window);

  sleep(3);

  i_close_window(run);
}
