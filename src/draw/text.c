#include <libinkX.h>

ink_text_obj i_create_new_text(ink_window_t window, int x, int y,
                               const char *text, const char *font) {
  if (font == NULL) {
    font = "fixed";
  }

  if (text == NULL) {
    text = "\n";
  }

  ink_text_obj itext = {
      .text = text,
      .font = font,
      .x = x,
      .y = y,
      .onclick = NULL,
      .onfocus = NULL,
  };

  return itext;
}

void i_set_text_onclick(ink_text_obj *itext, void (*onclick)(void)) {
  itext->onclick = onclick;
}
