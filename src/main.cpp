#include <iostream>
#include <emscripten.h>
#include <emscripten/bind.h>
#include "Emulator.h"

using namespace std;

auto *emulator = new Emulator();

void mainLoopCallback() {
  emulator->runCycle();
}

void setKey(char key, bool value) {
  emulator->keyboard->setKey(key, value);
}
EMSCRIPTEN_BINDINGS(my_module) {
  emscripten::function("setKey", &setKey);
}

int main() {  
  // TODO: clean up to handle requestAnimationFrame
  emscripten_set_main_loop(mainLoopCallback, 60, 1);
}