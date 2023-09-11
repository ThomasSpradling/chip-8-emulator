#include <emscripten.h>
#include <iostream>
#include "Display.h"

using namespace std;

void Display::drawDisplay(array<array<bool, 64>, 32> &display) {
  for (int i = 0; i < 32; i++) {
    for (int j = 0; j < 64; j++) {
      renderPixel(j, i, display[i][j]);
    }
  }
}

void Display::renderPixel(int x, int y, bool color) {
  EM_ASM({
    renderPixel($0, $1, $2);
  }, x, y, color);
}


void Display::shutDown() {}
