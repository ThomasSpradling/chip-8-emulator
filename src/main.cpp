#include <iostream>
#include <emscripten.h>
#include "Emulator.h"

using namespace std;

auto *emulator = new Emulator();

void mainLoopCallback() {
  emulator->runCycle();
}

int main() {  
  // TODO: clean up to handle requestAnimationFrame
  emscripten_set_main_loop(mainLoopCallback, 60, 1);
}