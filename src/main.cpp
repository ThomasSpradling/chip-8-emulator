#include "Emulator.h"

int main() {
  auto *emulator = new Emulator();
  
  // emscripten_set_main_loop(emulator->runCycle, 60, 1);
}