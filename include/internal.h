#ifndef __INK_INTERNAL_H_
#define __INK_INTERNAL_H_
#include <libinkX.h>

typedef enum {
  text,
  img,
  square,
} state_t;

typedef struct {
  state_t *states;
} window_state_t;

void i_text_draw(ink_text_obj obj, ink_run_window_t window);
void i_draw(state_t state);

#endif /* __INK_INTERNAL_H_ */
