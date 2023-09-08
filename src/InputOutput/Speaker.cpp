#include <emscripten.h>
#include "Speaker.h"

void Speaker::playSound() {
  EM_ASM(
    playSound();
  );
}
void Speaker::shutDown() {}